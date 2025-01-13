package ast

import "github.com/Siposattila/TestMe/tmtsl/token"

type Object struct {
	Token      *token.Token     `json:"-"`
	Name       string           `json:"name"`
	Properties []ObjectProperty `json:"properties,omitempty"`
}

type ObjectProperty struct {
	Token *token.Token `json:"-"`
	Key   string       `json:"key"`
	Value Expression   `json:"value"`
}

func (o Object) expressionNode()      {}
func (o Object) TokenLiteral() string { return string(o.Token.Lit) }

func NewObject(name, properties Attribute) (Object, error) {
	n, ok := name.(*token.Token)
	if !ok {
		return Object{}, astError("NewObject", "*token.Token", "name", name)
	}

	p, ok := properties.([]ObjectProperty)
	if !ok {
		return Object{}, astError("NewObject", "[]ObjectProperty", "properties", properties)
	}

	return Object{Token: n, Name: string(n.Lit), Properties: p}, nil
}

func NewObjectPropertyStringLiteral(key, value Attribute) (ObjectProperty, error) {
	k, ok := key.(*token.Token)
	if !ok {
		return ObjectProperty{}, astError("NewObjectPropertyStringLiteral", "*token.Token", "key", key)
	}

	v, ok := value.(*token.Token)
	if !ok {
		return ObjectProperty{}, astError("NewObjectPropertyStringLiteral", "Expression", "value", value)
	}

	sl, err := NewStringLiteral(v)
	if err != nil {
		return ObjectProperty{}, err
	}

	return ObjectProperty{Token: k, Key: string(k.Lit), Value: sl}, nil
}

func NewObjectPropertyIntegerLiteral(key, value Attribute) (ObjectProperty, error) {
	k, ok := key.(*token.Token)
	if !ok {
		return ObjectProperty{}, astError("NewObjectPropertyIntegerLiteral", "*token.Token", "key", key)
	}

	v, ok := value.(*token.Token)
	if !ok {
		return ObjectProperty{}, astError("NewObjectPropertyIntegerLiteral", "*token.Token", "value", value)
	}

	il, err := NewIntegerLiteral(v)
	if err != nil {
		return ObjectProperty{}, err
	}

	return ObjectProperty{Token: k, Key: string(k.Lit), Value: il}, nil
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
