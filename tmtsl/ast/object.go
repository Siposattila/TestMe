package ast

import "github.com/Siposattila/TestMe/tmtsl/token"

type Object struct {
	Token      *token.Token     `json:"-"`
	Name       StringLiteral    `json:"name"`
	Properties []ObjectProperty `json:"properties,omitempty"`
}

type ObjectProperty struct {
	Token *token.Token  `json:"-"`
	Key   StringLiteral `json:"key"`
	Value Expression    `json:"value"`
}

func (o Object) expressionNode()      {}
func (o Object) TokenLiteral() string { return string(o.Token.Lit) }

func (oy ObjectProperty) expressionNode()      {}
func (oy ObjectProperty) TokenLiteral() string { return string(oy.Token.Lit) }

func NewObject(name, properties Attribute) (Object, error) {
	n, ok := name.(StringLiteral)
	if !ok {
		return Object{}, astError("NewObject", "StringLiteral", "name", name)
	}

	p, ok := properties.([]ObjectProperty)
	if !ok {
		return Object{}, astError("NewObject", "[]ObjectProperty", "properties", properties)
	}

	return Object{Token: n.Token, Name: n, Properties: p}, nil
}

func NewObjectProperty(key, value Attribute) (ObjectProperty, error) {
	k, ok := key.(StringLiteral)
	if !ok {
		return ObjectProperty{}, astError("NewObjectProperty", "StringLiteral", "key", key)
	}

	v, ok := value.(Expression)
	if !ok {
		return ObjectProperty{}, astError("NewObjectProperty", "Expression", "value", value)
	}

	return ObjectProperty{Token: k.Token, Key: k, Value: v}, nil
}

func NewObjectPropertyList(expression Attribute) ([]ObjectProperty, error) {
	list := []ObjectProperty{}
	if expression != nil {
		t, ok := expression.(ObjectProperty)
		if !ok {
			return nil, astError("NewObjectPropertyList", "ObjectProperty", "expression", expression)
		}

		list = append(list, t)
	}

	return list, nil
}

func AppendObjectProperty(objectProperties, objectProperty Attribute) ([]ObjectProperty, error) {
	os, ok := objectProperties.([]ObjectProperty)
	if !ok {
		return nil, astError("AppendObjectProperty", "[]ObjectProperty", "objectProperties", objectProperties)
	}

	o, ok := objectProperty.(ObjectProperty)
	if !ok {
		return nil, astError("AppendObjectProperty", "ObjectProperty", "objectProperty", objectProperty)
	}

	return append(os, o), nil
}
