#include <ruby/ruby.h>

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

VALUE klass;

static void xml_free(void *doc) {
  xmlFreeDoc(doc);
}

VALUE search(VALUE self, VALUE xpathExpr)
{
  VALUE results = rb_ary_new();
  xmlDocPtr doc;
  Data_Get_Struct(self, xmlDoc, doc);

  xmlXPathContextPtr xpathCtx;
  xmlXPathObjectPtr xpathObj;
  xmlNodeSetPtr nodes;
  xmlNodePtr cur;
  int size;
  int i;
  
  xpathCtx = xmlXPathNewContext(doc);
  if (xpathCtx == NULL) {
    fprintf(stderr, "Error: unable to create new XPath context\n");
    xmlFreeDoc(doc);
    return -1;
  }

  xpathObj = xmlXPathEvalExpression(StringValueCStr(xpathExpr), xpathCtx);
  if (xpathObj == NULL) {
    fprintf(stderr, "Error: unable to evaluate xpath expression \"%s\"\n", StringValueCStr(xpathExpr));
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);
    return -1;
  }
  
  nodes = xpathObj->nodesetval;
  size = (nodes) ? nodes->nodeNr : 0;

  for (i = 0; i < size; ++i) {
    cur = nodes->nodeTab[i];
    rb_ary_push(results, rb_str_new2(xmlNodeGetContent(cur)));
  }

  xmlXPathFreeObject(xpathObj);
  xmlXPathFreeContext(xpathCtx);
  
  return results;
}

static VALUE initialize(VALUE self, VALUE filename) 
{
  rb_iv_set(self, "@filename", filename);
  return self;
}

static VALUE filename(VALUE self) 
{
  return rb_iv_get(self, "@filename");
}

VALUE constructor(VALUE self, VALUE filename) 
{
  xmlDocPtr doc;  
  VALUE argv[1];

  doc = xmlParseFile(StringValueCStr(filename));
  if (doc == NULL) {
    fprintf(stderr, "Error: unable to parse file \"%s\"\n", StringValueCStr(filename));
    return -1;
  }

  VALUE t_data = Data_Wrap_Struct(self, 0, xml_free, doc);
  argv[0] = filename;
  rb_obj_call_init(t_data, 1, argv);
  return t_data;
}

void Init_xpather()
{
  klass = rb_define_class("XPather", rb_cObject);
  rb_define_singleton_method(klass, "new", constructor, 1);
  rb_define_method(klass, "initialize", initialize, 1);
  rb_define_method(klass, "filename", filename, 0);
  rb_define_method(klass, "search", search, 1);
}
