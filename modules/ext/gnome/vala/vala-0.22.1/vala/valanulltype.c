/* valanulltype.c generated by valac, the Vala compiler
 * generated from valanulltype.vala, do not modify */

/* valanulltype.vala
 *
 * Copyright (C) 2007-2010  Jürg Billeter
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.

 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
 *
 * Author:
 * 	Jürg Billeter <j@bitron.ch>
 */

#include <glib.h>
#include <glib-object.h>
#include <stdlib.h>
#include <string.h>
#include <valagee.h>


#define VALA_TYPE_CODE_NODE (vala_code_node_get_type ())
#define VALA_CODE_NODE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), VALA_TYPE_CODE_NODE, ValaCodeNode))
#define VALA_CODE_NODE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), VALA_TYPE_CODE_NODE, ValaCodeNodeClass))
#define VALA_IS_CODE_NODE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), VALA_TYPE_CODE_NODE))
#define VALA_IS_CODE_NODE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), VALA_TYPE_CODE_NODE))
#define VALA_CODE_NODE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), VALA_TYPE_CODE_NODE, ValaCodeNodeClass))

typedef struct _ValaCodeNode ValaCodeNode;
typedef struct _ValaCodeNodeClass ValaCodeNodeClass;
typedef struct _ValaCodeNodePrivate ValaCodeNodePrivate;

#define VALA_TYPE_CODE_VISITOR (vala_code_visitor_get_type ())
#define VALA_CODE_VISITOR(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), VALA_TYPE_CODE_VISITOR, ValaCodeVisitor))
#define VALA_CODE_VISITOR_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), VALA_TYPE_CODE_VISITOR, ValaCodeVisitorClass))
#define VALA_IS_CODE_VISITOR(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), VALA_TYPE_CODE_VISITOR))
#define VALA_IS_CODE_VISITOR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), VALA_TYPE_CODE_VISITOR))
#define VALA_CODE_VISITOR_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), VALA_TYPE_CODE_VISITOR, ValaCodeVisitorClass))

typedef struct _ValaCodeVisitor ValaCodeVisitor;
typedef struct _ValaCodeVisitorClass ValaCodeVisitorClass;

#define VALA_TYPE_CODE_CONTEXT (vala_code_context_get_type ())
#define VALA_CODE_CONTEXT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), VALA_TYPE_CODE_CONTEXT, ValaCodeContext))
#define VALA_CODE_CONTEXT_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), VALA_TYPE_CODE_CONTEXT, ValaCodeContextClass))
#define VALA_IS_CODE_CONTEXT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), VALA_TYPE_CODE_CONTEXT))
#define VALA_IS_CODE_CONTEXT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), VALA_TYPE_CODE_CONTEXT))
#define VALA_CODE_CONTEXT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), VALA_TYPE_CODE_CONTEXT, ValaCodeContextClass))

typedef struct _ValaCodeContext ValaCodeContext;
typedef struct _ValaCodeContextClass ValaCodeContextClass;

#define VALA_TYPE_CODE_GENERATOR (vala_code_generator_get_type ())
#define VALA_CODE_GENERATOR(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), VALA_TYPE_CODE_GENERATOR, ValaCodeGenerator))
#define VALA_CODE_GENERATOR_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), VALA_TYPE_CODE_GENERATOR, ValaCodeGeneratorClass))
#define VALA_IS_CODE_GENERATOR(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), VALA_TYPE_CODE_GENERATOR))
#define VALA_IS_CODE_GENERATOR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), VALA_TYPE_CODE_GENERATOR))
#define VALA_CODE_GENERATOR_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), VALA_TYPE_CODE_GENERATOR, ValaCodeGeneratorClass))

typedef struct _ValaCodeGenerator ValaCodeGenerator;
typedef struct _ValaCodeGeneratorClass ValaCodeGeneratorClass;

#define VALA_TYPE_DATA_TYPE (vala_data_type_get_type ())
#define VALA_DATA_TYPE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), VALA_TYPE_DATA_TYPE, ValaDataType))
#define VALA_DATA_TYPE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), VALA_TYPE_DATA_TYPE, ValaDataTypeClass))
#define VALA_IS_DATA_TYPE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), VALA_TYPE_DATA_TYPE))
#define VALA_IS_DATA_TYPE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), VALA_TYPE_DATA_TYPE))
#define VALA_DATA_TYPE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), VALA_TYPE_DATA_TYPE, ValaDataTypeClass))

typedef struct _ValaDataType ValaDataType;
typedef struct _ValaDataTypeClass ValaDataTypeClass;

#define VALA_TYPE_EXPRESSION (vala_expression_get_type ())
#define VALA_EXPRESSION(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), VALA_TYPE_EXPRESSION, ValaExpression))
#define VALA_EXPRESSION_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), VALA_TYPE_EXPRESSION, ValaExpressionClass))
#define VALA_IS_EXPRESSION(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), VALA_TYPE_EXPRESSION))
#define VALA_IS_EXPRESSION_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), VALA_TYPE_EXPRESSION))
#define VALA_EXPRESSION_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), VALA_TYPE_EXPRESSION, ValaExpressionClass))

typedef struct _ValaExpression ValaExpression;
typedef struct _ValaExpressionClass ValaExpressionClass;

#define VALA_TYPE_SYMBOL (vala_symbol_get_type ())
#define VALA_SYMBOL(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), VALA_TYPE_SYMBOL, ValaSymbol))
#define VALA_SYMBOL_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), VALA_TYPE_SYMBOL, ValaSymbolClass))
#define VALA_IS_SYMBOL(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), VALA_TYPE_SYMBOL))
#define VALA_IS_SYMBOL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), VALA_TYPE_SYMBOL))
#define VALA_SYMBOL_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), VALA_TYPE_SYMBOL, ValaSymbolClass))

typedef struct _ValaSymbol ValaSymbol;
typedef struct _ValaSymbolClass ValaSymbolClass;

#define VALA_TYPE_VARIABLE (vala_variable_get_type ())
#define VALA_VARIABLE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), VALA_TYPE_VARIABLE, ValaVariable))
#define VALA_VARIABLE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), VALA_TYPE_VARIABLE, ValaVariableClass))
#define VALA_IS_VARIABLE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), VALA_TYPE_VARIABLE))
#define VALA_IS_VARIABLE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), VALA_TYPE_VARIABLE))
#define VALA_VARIABLE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), VALA_TYPE_VARIABLE, ValaVariableClass))

typedef struct _ValaVariable ValaVariable;
typedef struct _ValaVariableClass ValaVariableClass;

#define VALA_TYPE_ATTRIBUTE (vala_attribute_get_type ())
#define VALA_ATTRIBUTE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), VALA_TYPE_ATTRIBUTE, ValaAttribute))
#define VALA_ATTRIBUTE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), VALA_TYPE_ATTRIBUTE, ValaAttributeClass))
#define VALA_IS_ATTRIBUTE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), VALA_TYPE_ATTRIBUTE))
#define VALA_IS_ATTRIBUTE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), VALA_TYPE_ATTRIBUTE))
#define VALA_ATTRIBUTE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), VALA_TYPE_ATTRIBUTE, ValaAttributeClass))

typedef struct _ValaAttribute ValaAttribute;
typedef struct _ValaAttributeClass ValaAttributeClass;
typedef struct _ValaDataTypePrivate ValaDataTypePrivate;

#define VALA_TYPE_SCOPE (vala_scope_get_type ())
#define VALA_SCOPE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), VALA_TYPE_SCOPE, ValaScope))
#define VALA_SCOPE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), VALA_TYPE_SCOPE, ValaScopeClass))
#define VALA_IS_SCOPE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), VALA_TYPE_SCOPE))
#define VALA_IS_SCOPE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), VALA_TYPE_SCOPE))
#define VALA_SCOPE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), VALA_TYPE_SCOPE, ValaScopeClass))

typedef struct _ValaScope ValaScope;
typedef struct _ValaScopeClass ValaScopeClass;

#define VALA_TYPE_PARAMETER (vala_parameter_get_type ())
#define VALA_PARAMETER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), VALA_TYPE_PARAMETER, ValaParameter))
#define VALA_PARAMETER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), VALA_TYPE_PARAMETER, ValaParameterClass))
#define VALA_IS_PARAMETER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), VALA_TYPE_PARAMETER))
#define VALA_IS_PARAMETER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), VALA_TYPE_PARAMETER))
#define VALA_PARAMETER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), VALA_TYPE_PARAMETER, ValaParameterClass))

typedef struct _ValaParameter ValaParameter;
typedef struct _ValaParameterClass ValaParameterClass;

#define VALA_TYPE_MEMBER_ACCESS (vala_member_access_get_type ())
#define VALA_MEMBER_ACCESS(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), VALA_TYPE_MEMBER_ACCESS, ValaMemberAccess))
#define VALA_MEMBER_ACCESS_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), VALA_TYPE_MEMBER_ACCESS, ValaMemberAccessClass))
#define VALA_IS_MEMBER_ACCESS(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), VALA_TYPE_MEMBER_ACCESS))
#define VALA_IS_MEMBER_ACCESS_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), VALA_TYPE_MEMBER_ACCESS))
#define VALA_MEMBER_ACCESS_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), VALA_TYPE_MEMBER_ACCESS, ValaMemberAccessClass))

typedef struct _ValaMemberAccess ValaMemberAccess;
typedef struct _ValaMemberAccessClass ValaMemberAccessClass;

#define VALA_TYPE_REFERENCE_TYPE (vala_reference_type_get_type ())
#define VALA_REFERENCE_TYPE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), VALA_TYPE_REFERENCE_TYPE, ValaReferenceType))
#define VALA_REFERENCE_TYPE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), VALA_TYPE_REFERENCE_TYPE, ValaReferenceTypeClass))
#define VALA_IS_REFERENCE_TYPE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), VALA_TYPE_REFERENCE_TYPE))
#define VALA_IS_REFERENCE_TYPE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), VALA_TYPE_REFERENCE_TYPE))
#define VALA_REFERENCE_TYPE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), VALA_TYPE_REFERENCE_TYPE, ValaReferenceTypeClass))

typedef struct _ValaReferenceType ValaReferenceType;
typedef struct _ValaReferenceTypeClass ValaReferenceTypeClass;
typedef struct _ValaReferenceTypePrivate ValaReferenceTypePrivate;

#define VALA_TYPE_NULL_TYPE (vala_null_type_get_type ())
#define VALA_NULL_TYPE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), VALA_TYPE_NULL_TYPE, ValaNullType))
#define VALA_NULL_TYPE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), VALA_TYPE_NULL_TYPE, ValaNullTypeClass))
#define VALA_IS_NULL_TYPE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), VALA_TYPE_NULL_TYPE))
#define VALA_IS_NULL_TYPE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), VALA_TYPE_NULL_TYPE))
#define VALA_NULL_TYPE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), VALA_TYPE_NULL_TYPE, ValaNullTypeClass))

typedef struct _ValaNullType ValaNullType;
typedef struct _ValaNullTypeClass ValaNullTypeClass;
typedef struct _ValaNullTypePrivate ValaNullTypePrivate;

#define VALA_TYPE_SOURCE_REFERENCE (vala_source_reference_get_type ())
#define VALA_SOURCE_REFERENCE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), VALA_TYPE_SOURCE_REFERENCE, ValaSourceReference))
#define VALA_SOURCE_REFERENCE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), VALA_TYPE_SOURCE_REFERENCE, ValaSourceReferenceClass))
#define VALA_IS_SOURCE_REFERENCE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), VALA_TYPE_SOURCE_REFERENCE))
#define VALA_IS_SOURCE_REFERENCE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), VALA_TYPE_SOURCE_REFERENCE))
#define VALA_SOURCE_REFERENCE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), VALA_TYPE_SOURCE_REFERENCE, ValaSourceReferenceClass))

typedef struct _ValaSourceReference ValaSourceReference;
typedef struct _ValaSourceReferenceClass ValaSourceReferenceClass;
#define _vala_code_context_unref0(var) ((var == NULL) ? NULL : (var = (vala_code_context_unref (var), NULL)))

#define VALA_TYPE_POINTER_TYPE (vala_pointer_type_get_type ())
#define VALA_POINTER_TYPE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), VALA_TYPE_POINTER_TYPE, ValaPointerType))
#define VALA_POINTER_TYPE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), VALA_TYPE_POINTER_TYPE, ValaPointerTypeClass))
#define VALA_IS_POINTER_TYPE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), VALA_TYPE_POINTER_TYPE))
#define VALA_IS_POINTER_TYPE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), VALA_TYPE_POINTER_TYPE))
#define VALA_POINTER_TYPE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), VALA_TYPE_POINTER_TYPE, ValaPointerTypeClass))

typedef struct _ValaPointerType ValaPointerType;
typedef struct _ValaPointerTypeClass ValaPointerTypeClass;

#define VALA_TYPE_TYPESYMBOL (vala_typesymbol_get_type ())
#define VALA_TYPESYMBOL(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), VALA_TYPE_TYPESYMBOL, ValaTypeSymbol))
#define VALA_TYPESYMBOL_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), VALA_TYPE_TYPESYMBOL, ValaTypeSymbolClass))
#define VALA_IS_TYPESYMBOL(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), VALA_TYPE_TYPESYMBOL))
#define VALA_IS_TYPESYMBOL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), VALA_TYPE_TYPESYMBOL))
#define VALA_TYPESYMBOL_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), VALA_TYPE_TYPESYMBOL, ValaTypeSymbolClass))

typedef struct _ValaTypeSymbol ValaTypeSymbol;
typedef struct _ValaTypeSymbolClass ValaTypeSymbolClass;

#define VALA_TYPE_TYPEPARAMETER (vala_typeparameter_get_type ())
#define VALA_TYPEPARAMETER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), VALA_TYPE_TYPEPARAMETER, ValaTypeParameter))
#define VALA_TYPEPARAMETER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), VALA_TYPE_TYPEPARAMETER, ValaTypeParameterClass))
#define VALA_IS_TYPEPARAMETER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), VALA_TYPE_TYPEPARAMETER))
#define VALA_IS_TYPEPARAMETER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), VALA_TYPE_TYPEPARAMETER))
#define VALA_TYPEPARAMETER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), VALA_TYPE_TYPEPARAMETER, ValaTypeParameterClass))

typedef struct _ValaTypeParameter ValaTypeParameter;
typedef struct _ValaTypeParameterClass ValaTypeParameterClass;
#define _vala_code_node_unref0(var) ((var == NULL) ? NULL : (var = (vala_code_node_unref (var), NULL)))

#define VALA_TYPE_ARRAY_TYPE (vala_array_type_get_type ())
#define VALA_ARRAY_TYPE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), VALA_TYPE_ARRAY_TYPE, ValaArrayType))
#define VALA_ARRAY_TYPE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), VALA_TYPE_ARRAY_TYPE, ValaArrayTypeClass))
#define VALA_IS_ARRAY_TYPE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), VALA_TYPE_ARRAY_TYPE))
#define VALA_IS_ARRAY_TYPE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), VALA_TYPE_ARRAY_TYPE))
#define VALA_ARRAY_TYPE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), VALA_TYPE_ARRAY_TYPE, ValaArrayTypeClass))

typedef struct _ValaArrayType ValaArrayType;
typedef struct _ValaArrayTypeClass ValaArrayTypeClass;

#define VALA_TYPE_DELEGATE_TYPE (vala_delegate_type_get_type ())
#define VALA_DELEGATE_TYPE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), VALA_TYPE_DELEGATE_TYPE, ValaDelegateType))
#define VALA_DELEGATE_TYPE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), VALA_TYPE_DELEGATE_TYPE, ValaDelegateTypeClass))
#define VALA_IS_DELEGATE_TYPE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), VALA_TYPE_DELEGATE_TYPE))
#define VALA_IS_DELEGATE_TYPE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), VALA_TYPE_DELEGATE_TYPE))
#define VALA_DELEGATE_TYPE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), VALA_TYPE_DELEGATE_TYPE, ValaDelegateTypeClass))

typedef struct _ValaDelegateType ValaDelegateType;
typedef struct _ValaDelegateTypeClass ValaDelegateTypeClass;

struct _ValaCodeNode {
	GTypeInstance parent_instance;
	volatile int ref_count;
	ValaCodeNodePrivate * priv;
	GList* attributes;
};

struct _ValaCodeNodeClass {
	GTypeClass parent_class;
	void (*finalize) (ValaCodeNode *self);
	void (*accept) (ValaCodeNode* self, ValaCodeVisitor* visitor);
	void (*accept_children) (ValaCodeNode* self, ValaCodeVisitor* visitor);
	gboolean (*check) (ValaCodeNode* self, ValaCodeContext* context);
	void (*emit) (ValaCodeNode* self, ValaCodeGenerator* codegen);
	void (*replace_type) (ValaCodeNode* self, ValaDataType* old_type, ValaDataType* new_type);
	void (*replace_expression) (ValaCodeNode* self, ValaExpression* old_node, ValaExpression* new_node);
	gchar* (*to_string) (ValaCodeNode* self);
	void (*get_defined_variables) (ValaCodeNode* self, ValaCollection* collection);
	void (*get_used_variables) (ValaCodeNode* self, ValaCollection* collection);
};

struct _ValaDataType {
	ValaCodeNode parent_instance;
	ValaDataTypePrivate * priv;
};

struct _ValaDataTypeClass {
	ValaCodeNodeClass parent_class;
	gchar* (*to_qualified_string) (ValaDataType* self, ValaScope* scope);
	ValaDataType* (*copy) (ValaDataType* self);
	gboolean (*equals) (ValaDataType* self, ValaDataType* type2);
	gboolean (*stricter) (ValaDataType* self, ValaDataType* type2);
	gboolean (*compatible) (ValaDataType* self, ValaDataType* target_type);
	gboolean (*is_invokable) (ValaDataType* self);
	ValaDataType* (*get_return_type) (ValaDataType* self);
	ValaList* (*get_parameters) (ValaDataType* self);
	gboolean (*is_reference_type_or_type_parameter) (ValaDataType* self);
	gboolean (*is_array) (ValaDataType* self);
	gboolean (*is_accessible) (ValaDataType* self, ValaSymbol* sym);
	ValaSymbol* (*get_member) (ValaDataType* self, const gchar* member_name);
	ValaSymbol* (*get_pointer_member) (ValaDataType* self, const gchar* member_name);
	gboolean (*is_real_struct_type) (ValaDataType* self);
	gboolean (*is_disposable) (ValaDataType* self);
	ValaDataType* (*get_actual_type) (ValaDataType* self, ValaDataType* derived_instance_type, ValaMemberAccess* method_access, ValaCodeNode* node_reference);
};

struct _ValaReferenceType {
	ValaDataType parent_instance;
	ValaReferenceTypePrivate * priv;
};

struct _ValaReferenceTypeClass {
	ValaDataTypeClass parent_class;
};

struct _ValaNullType {
	ValaReferenceType parent_instance;
	ValaNullTypePrivate * priv;
};

struct _ValaNullTypeClass {
	ValaReferenceTypeClass parent_class;
};


static gpointer vala_null_type_parent_class = NULL;

gpointer vala_code_node_ref (gpointer instance);
void vala_code_node_unref (gpointer instance);
GParamSpec* vala_param_spec_code_node (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags);
void vala_value_set_code_node (GValue* value, gpointer v_object);
void vala_value_take_code_node (GValue* value, gpointer v_object);
gpointer vala_value_get_code_node (const GValue* value);
GType vala_code_node_get_type (void) G_GNUC_CONST;
gpointer vala_code_visitor_ref (gpointer instance);
void vala_code_visitor_unref (gpointer instance);
GParamSpec* vala_param_spec_code_visitor (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags);
void vala_value_set_code_visitor (GValue* value, gpointer v_object);
void vala_value_take_code_visitor (GValue* value, gpointer v_object);
gpointer vala_value_get_code_visitor (const GValue* value);
GType vala_code_visitor_get_type (void) G_GNUC_CONST;
gpointer vala_code_context_ref (gpointer instance);
void vala_code_context_unref (gpointer instance);
GParamSpec* vala_param_spec_code_context (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags);
void vala_value_set_code_context (GValue* value, gpointer v_object);
void vala_value_take_code_context (GValue* value, gpointer v_object);
gpointer vala_value_get_code_context (const GValue* value);
GType vala_code_context_get_type (void) G_GNUC_CONST;
GType vala_code_generator_get_type (void) G_GNUC_CONST;
GType vala_data_type_get_type (void) G_GNUC_CONST;
GType vala_expression_get_type (void) G_GNUC_CONST;
GType vala_symbol_get_type (void) G_GNUC_CONST;
GType vala_variable_get_type (void) G_GNUC_CONST;
GType vala_attribute_get_type (void) G_GNUC_CONST;
gpointer vala_scope_ref (gpointer instance);
void vala_scope_unref (gpointer instance);
GParamSpec* vala_param_spec_scope (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags);
void vala_value_set_scope (GValue* value, gpointer v_object);
void vala_value_take_scope (GValue* value, gpointer v_object);
gpointer vala_value_get_scope (const GValue* value);
GType vala_scope_get_type (void) G_GNUC_CONST;
GType vala_parameter_get_type (void) G_GNUC_CONST;
GType vala_member_access_get_type (void) G_GNUC_CONST;
GType vala_reference_type_get_type (void) G_GNUC_CONST;
GType vala_null_type_get_type (void) G_GNUC_CONST;
enum  {
	VALA_NULL_TYPE_DUMMY_PROPERTY
};
gpointer vala_source_reference_ref (gpointer instance);
void vala_source_reference_unref (gpointer instance);
GParamSpec* vala_param_spec_source_reference (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags);
void vala_value_set_source_reference (GValue* value, gpointer v_object);
void vala_value_take_source_reference (GValue* value, gpointer v_object);
gpointer vala_value_get_source_reference (const GValue* value);
GType vala_source_reference_get_type (void) G_GNUC_CONST;
ValaNullType* vala_null_type_new (ValaSourceReference* source_reference);
ValaNullType* vala_null_type_construct (GType object_type, ValaSourceReference* source_reference);
ValaReferenceType* vala_reference_type_construct (GType object_type);
void vala_data_type_set_nullable (ValaDataType* self, gboolean value);
void vala_code_node_set_source_reference (ValaCodeNode* self, ValaSourceReference* value);
static gboolean vala_null_type_real_compatible (ValaDataType* base, ValaDataType* target_type);
ValaCodeContext* vala_code_context_get (void);
gboolean vala_code_context_get_experimental_non_null (ValaCodeContext* self);
gboolean vala_data_type_get_nullable (ValaDataType* self);
GType vala_pointer_type_get_type (void) G_GNUC_CONST;
GType vala_typesymbol_get_type (void) G_GNUC_CONST;
ValaTypeSymbol* vala_data_type_get_data_type (ValaDataType* self);
GType vala_typeparameter_get_type (void) G_GNUC_CONST;
ValaTypeParameter* vala_data_type_get_type_parameter (ValaDataType* self);
ValaAttribute* vala_code_node_get_attribute (ValaCodeNode* self, const gchar* name);
gboolean vala_typesymbol_is_reference_type (ValaTypeSymbol* self);
GType vala_array_type_get_type (void) G_GNUC_CONST;
GType vala_delegate_type_get_type (void) G_GNUC_CONST;
static ValaDataType* vala_null_type_real_copy (ValaDataType* base);
ValaSourceReference* vala_code_node_get_source_reference (ValaCodeNode* self);
static gboolean vala_null_type_real_is_disposable (ValaDataType* base);
static gchar* vala_null_type_real_to_qualified_string (ValaDataType* base, ValaScope* scope);


ValaNullType* vala_null_type_construct (GType object_type, ValaSourceReference* source_reference) {
	ValaNullType* self = NULL;
	ValaSourceReference* _tmp0_ = NULL;
	self = (ValaNullType*) vala_reference_type_construct (object_type);
	vala_data_type_set_nullable ((ValaDataType*) self, TRUE);
	_tmp0_ = source_reference;
	vala_code_node_set_source_reference ((ValaCodeNode*) self, _tmp0_);
	return self;
}


ValaNullType* vala_null_type_new (ValaSourceReference* source_reference) {
	return vala_null_type_construct (VALA_TYPE_NULL_TYPE, source_reference);
}


static gboolean vala_null_type_real_compatible (ValaDataType* base, ValaDataType* target_type) {
	ValaNullType * self;
	gboolean result = FALSE;
	ValaCodeContext* _tmp0_ = NULL;
	ValaCodeContext* _tmp1_ = NULL;
	gboolean _tmp2_ = FALSE;
	gboolean _tmp3_ = FALSE;
	gboolean _tmp4_ = FALSE;
	gboolean _tmp8_ = FALSE;
	ValaDataType* _tmp9_ = NULL;
	gboolean _tmp21_ = FALSE;
	gboolean _tmp22_ = FALSE;
	gboolean _tmp23_ = FALSE;
	gboolean _tmp24_ = FALSE;
	ValaDataType* _tmp25_ = NULL;
	ValaTypeParameter* _tmp26_ = NULL;
	ValaTypeParameter* _tmp27_ = NULL;
	gboolean _tmp29_ = FALSE;
	gboolean _tmp33_ = FALSE;
	gboolean _tmp39_ = FALSE;
	gboolean _tmp40_ = FALSE;
	gboolean _tmp41_ = FALSE;
	ValaDataType* _tmp42_ = NULL;
	ValaTypeSymbol* _tmp43_ = NULL;
	ValaTypeSymbol* _tmp44_ = NULL;
	gboolean _tmp45_ = FALSE;
	gboolean _tmp47_ = FALSE;
	gboolean _tmp49_ = FALSE;
	self = (ValaNullType*) base;
	g_return_val_if_fail (target_type != NULL, FALSE);
	_tmp0_ = vala_code_context_get ();
	_tmp1_ = _tmp0_;
	_tmp2_ = vala_code_context_get_experimental_non_null (_tmp1_);
	_tmp3_ = _tmp2_;
	_tmp4_ = _tmp3_;
	_vala_code_context_unref0 (_tmp1_);
	if (_tmp4_) {
		ValaDataType* _tmp5_ = NULL;
		gboolean _tmp6_ = FALSE;
		gboolean _tmp7_ = FALSE;
		_tmp5_ = target_type;
		_tmp6_ = vala_data_type_get_nullable (_tmp5_);
		_tmp7_ = _tmp6_;
		result = _tmp7_;
		return result;
	}
	_tmp9_ = target_type;
	if (!G_TYPE_CHECK_INSTANCE_TYPE (_tmp9_, VALA_TYPE_POINTER_TYPE)) {
		gboolean _tmp10_ = FALSE;
		ValaDataType* _tmp11_ = NULL;
		gboolean _tmp20_ = FALSE;
		_tmp11_ = target_type;
		if (G_TYPE_CHECK_INSTANCE_TYPE (_tmp11_, VALA_TYPE_NULL_TYPE)) {
			_tmp10_ = TRUE;
		} else {
			gboolean _tmp12_ = FALSE;
			ValaDataType* _tmp13_ = NULL;
			ValaTypeSymbol* _tmp14_ = NULL;
			ValaTypeSymbol* _tmp15_ = NULL;
			gboolean _tmp19_ = FALSE;
			_tmp13_ = target_type;
			_tmp14_ = vala_data_type_get_data_type (_tmp13_);
			_tmp15_ = _tmp14_;
			if (_tmp15_ == NULL) {
				ValaDataType* _tmp16_ = NULL;
				ValaTypeParameter* _tmp17_ = NULL;
				ValaTypeParameter* _tmp18_ = NULL;
				_tmp16_ = target_type;
				_tmp17_ = vala_data_type_get_type_parameter (_tmp16_);
				_tmp18_ = _tmp17_;
				_tmp12_ = _tmp18_ == NULL;
			} else {
				_tmp12_ = FALSE;
			}
			_tmp19_ = _tmp12_;
			_tmp10_ = _tmp19_;
		}
		_tmp20_ = _tmp10_;
		_tmp8_ = _tmp20_;
	} else {
		_tmp8_ = FALSE;
	}
	_tmp21_ = _tmp8_;
	if (_tmp21_) {
		result = TRUE;
		return result;
	}
	_tmp25_ = target_type;
	_tmp26_ = vala_data_type_get_type_parameter (_tmp25_);
	_tmp27_ = _tmp26_;
	if (_tmp27_ != NULL) {
		_tmp24_ = TRUE;
	} else {
		ValaDataType* _tmp28_ = NULL;
		_tmp28_ = target_type;
		_tmp24_ = G_TYPE_CHECK_INSTANCE_TYPE (_tmp28_, VALA_TYPE_POINTER_TYPE);
	}
	_tmp29_ = _tmp24_;
	if (_tmp29_) {
		_tmp23_ = TRUE;
	} else {
		ValaDataType* _tmp30_ = NULL;
		gboolean _tmp31_ = FALSE;
		gboolean _tmp32_ = FALSE;
		_tmp30_ = target_type;
		_tmp31_ = vala_data_type_get_nullable (_tmp30_);
		_tmp32_ = _tmp31_;
		_tmp23_ = _tmp32_;
	}
	_tmp33_ = _tmp23_;
	if (_tmp33_) {
		_tmp22_ = TRUE;
	} else {
		ValaDataType* _tmp34_ = NULL;
		ValaTypeSymbol* _tmp35_ = NULL;
		ValaTypeSymbol* _tmp36_ = NULL;
		ValaAttribute* _tmp37_ = NULL;
		ValaAttribute* _tmp38_ = NULL;
		_tmp34_ = target_type;
		_tmp35_ = vala_data_type_get_data_type (_tmp34_);
		_tmp36_ = _tmp35_;
		_tmp37_ = vala_code_node_get_attribute ((ValaCodeNode*) _tmp36_, "PointerType");
		_tmp38_ = _tmp37_;
		_tmp22_ = _tmp38_ != NULL;
		_vala_code_node_unref0 (_tmp38_);
	}
	_tmp39_ = _tmp22_;
	if (_tmp39_) {
		result = TRUE;
		return result;
	}
	_tmp42_ = target_type;
	_tmp43_ = vala_data_type_get_data_type (_tmp42_);
	_tmp44_ = _tmp43_;
	_tmp45_ = vala_typesymbol_is_reference_type (_tmp44_);
	if (_tmp45_) {
		_tmp41_ = TRUE;
	} else {
		ValaDataType* _tmp46_ = NULL;
		_tmp46_ = target_type;
		_tmp41_ = G_TYPE_CHECK_INSTANCE_TYPE (_tmp46_, VALA_TYPE_ARRAY_TYPE);
	}
	_tmp47_ = _tmp41_;
	if (_tmp47_) {
		_tmp40_ = TRUE;
	} else {
		ValaDataType* _tmp48_ = NULL;
		_tmp48_ = target_type;
		_tmp40_ = G_TYPE_CHECK_INSTANCE_TYPE (_tmp48_, VALA_TYPE_DELEGATE_TYPE);
	}
	_tmp49_ = _tmp40_;
	if (_tmp49_) {
		result = TRUE;
		return result;
	}
	result = FALSE;
	return result;
}


static ValaDataType* vala_null_type_real_copy (ValaDataType* base) {
	ValaNullType * self;
	ValaDataType* result = NULL;
	ValaSourceReference* _tmp0_ = NULL;
	ValaSourceReference* _tmp1_ = NULL;
	ValaNullType* _tmp2_ = NULL;
	self = (ValaNullType*) base;
	_tmp0_ = vala_code_node_get_source_reference ((ValaCodeNode*) self);
	_tmp1_ = _tmp0_;
	_tmp2_ = vala_null_type_new (_tmp1_);
	result = (ValaDataType*) _tmp2_;
	return result;
}


static gboolean vala_null_type_real_is_disposable (ValaDataType* base) {
	ValaNullType * self;
	gboolean result = FALSE;
	self = (ValaNullType*) base;
	result = FALSE;
	return result;
}


static gchar* vala_null_type_real_to_qualified_string (ValaDataType* base, ValaScope* scope) {
	ValaNullType * self;
	gchar* result = NULL;
	gchar* _tmp0_ = NULL;
	self = (ValaNullType*) base;
	_tmp0_ = g_strdup ("null");
	result = _tmp0_;
	return result;
}


static void vala_null_type_class_init (ValaNullTypeClass * klass) {
	vala_null_type_parent_class = g_type_class_peek_parent (klass);
	VALA_DATA_TYPE_CLASS (klass)->compatible = vala_null_type_real_compatible;
	VALA_DATA_TYPE_CLASS (klass)->copy = vala_null_type_real_copy;
	VALA_DATA_TYPE_CLASS (klass)->is_disposable = vala_null_type_real_is_disposable;
	VALA_DATA_TYPE_CLASS (klass)->to_qualified_string = vala_null_type_real_to_qualified_string;
}


static void vala_null_type_instance_init (ValaNullType * self) {
}


/**
 * The type of the null literal.
 */
GType vala_null_type_get_type (void) {
	static volatile gsize vala_null_type_type_id__volatile = 0;
	if (g_once_init_enter (&vala_null_type_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (ValaNullTypeClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) vala_null_type_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (ValaNullType), 0, (GInstanceInitFunc) vala_null_type_instance_init, NULL };
		GType vala_null_type_type_id;
		vala_null_type_type_id = g_type_register_static (VALA_TYPE_REFERENCE_TYPE, "ValaNullType", &g_define_type_info, 0);
		g_once_init_leave (&vala_null_type_type_id__volatile, vala_null_type_type_id);
	}
	return vala_null_type_type_id__volatile;
}



