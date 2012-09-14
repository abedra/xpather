#include <ruby/ruby.h>

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

static void xml_free(void *doc) {
  xmlFreeDoc(doc);
}

VALUE search(VALUE self, VALUE xpathExpr)
{
  VALUE results = rb_ary_new();
  xmlDocPtr doc;
  xmlXPathContextPtr xpathCtx;
  xmlXPathObjectPtr xpathObj;
  xmlNodeSetPtr nodes;
  xmlNodePtr cur;
  int size;
  int i;

  Data_Get_Struct(self, xmlDoc, doc);

  xpathCtx = xmlXPathNewContext(doc);
  if (xpathCtx == NULL) {
    rb_raise(rb_eArgError, "Error: unable to create new XPath context\n");
    return Qnil;
  }

  xpathObj = xmlXPathEvalExpression(StringValueCStr(xpathExpr), xpathCtx);
  if (xpathObj == NULL) {
    rb_raise(rb_eArgError, "Error: unable to evaluate xpath expression \"%s\"\n", StringValueCStr(xpathExpr));
    xmlXPathFreeContext(xpathCtx);
    return Qnil;
  }

  nodes = xpathObj->nodesetval;
  size = (nodes) ? nodes->nodeNr : 0;

  if (size == 1) {
    results = rb_str_new2(xmlNodeGetContent(nodes->nodeTab[0]));
  } else if (size > 1) {
    for (i = 0; i < size; ++i) {
      cur = nodes->nodeTab[i];
      rb_ary_push(results, rb_str_new2(xmlNodeGetContent(cur)));
    }
  } else {
    return Qnil;
  }

  xmlXPathFreeObject(xpathObj);
  xmlXPathFreeContext(xpathCtx);

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

  doc = xmlParseMemory(xmlCStr, strlen(xmlCStr));
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
}
