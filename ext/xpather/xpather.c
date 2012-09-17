#include <ruby/ruby.h>

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

static void xml_free(void *doc) {
  xmlFreeDoc(doc);
}

xmlXPathObjectPtr eval_and_search(xmlDocPtr doc, char *query) {
  xmlXPathContextPtr xpathCtx;
  xmlXPathObjectPtr xpathObj;

  xpathCtx = xmlXPathNewContext(doc);
  if (xpathCtx == NULL) {
    rb_raise(rb_eArgError, "Error: unable to create new XPath context\n");
    return NULL;
  }

  xpathObj = xmlXPathEvalExpression(query, xpathCtx);
  if (xpathObj == NULL) {
    rb_raise(rb_eArgError, "Error: unable to evaluate xpath expression \"%s\"\n", query);
    xmlXPathFreeContext(xpathCtx);
    return NULL;
  }

  xmlXPathFreeContext(xpathCtx);

  return xpathObj;
}

VALUE get(VALUE self, VALUE xpathExpr)
{
  VALUE results = rb_ary_new();
  xmlDocPtr doc;
  xmlXPathObjectPtr xpathObj;
  xmlNodeSetPtr nodes;
  xmlNodePtr current;
  int size, i;

  Data_Get_Struct(self, xmlDoc, doc);

  xpathObj = eval_and_search(doc, StringValueCStr(xpathExpr));

  if (xpathObj == NULL) { return Qnil; }

  nodes = xpathObj->nodesetval;
  size = (nodes) ? nodes->nodeNr : 0;

  if (size == 0) { return Qnil; }

  if (size == 1) {
    results = rb_str_new2(xmlNodeGetContent(nodes->nodeTab[0]));
  } else {
    for (i = 0; i < size; i++) {
      current = nodes->nodeTab[i];
      rb_ary_push(results, rb_str_new2(xmlNodeGetContent(current)));
    }
  }

  xmlXPathFreeObject(xpathObj);

  return results;
}

VALUE search(VALUE self, VALUE xpathExpr)
{
  VALUE results = rb_ary_new();
  xmlDocPtr doc;
  xmlXPathObjectPtr xpathObj;
  xmlNodeSetPtr nodes;
  xmlNodePtr cur;
  xmlBufferPtr nodeBuffer;
  int size, i;

  Data_Get_Struct(self, xmlDoc, doc);

  xpathObj = eval_and_search(doc, StringValueCStr(xpathExpr));

  if (xpathObj == NULL) { return Qnil; }

  nodes = xpathObj->nodesetval;
  size = (nodes) ? nodes->nodeNr : 0;

  for (i = 0; i < size; ++i) {
    nodeBuffer = xmlBufferCreate();
    xmlNodeDump(nodeBuffer, doc, nodes->nodeTab[i], 0, 1);
    rb_ary_push(results, rb_str_new2(nodeBuffer->content));
    xmlBufferFree(nodeBuffer);
  }

  xmlXPathFreeObject(xpathObj);

  return results;
}

static VALUE initialize(VALUE self, VALUE xmlStr)
{
  rb_iv_set(self, "@xml_str", xmlStr);
  return self;
}

VALUE constructor(VALUE self, VALUE xmlStr)
{
  xmlDocPtr doc;
  const char *xmlCStr = StringValueCStr(xmlStr);
  VALUE argv[1];
  VALUE t_data;

  doc = xmlParseMemory(xmlCStr, (int)strlen(xmlCStr));
  if (doc == NULL) {
    fprintf(stderr, "Error: unable to parse xml\n");
    return Qnil;
  }

  t_data = Data_Wrap_Struct(self, 0, xml_free, doc);
  argv[0] = xmlStr;
  rb_obj_call_init(t_data, 1, argv);
  return t_data;
}

void Init_xpather(void)
{
  VALUE klass = rb_define_class("XPather", rb_cObject);
  rb_define_singleton_method(klass, "new", constructor, 1);
  rb_define_method(klass, "initialize", initialize, 1);
  rb_define_method(klass, "search", search, 1);
  rb_define_method(klass, "get", get, 1);
}
