package ast

import (
	"fmt"
	"strconv"

	"github.com/Siposattila/TestMe/tmtsl/token"
)

func astError(function string, expected string, variable string, got interface{}) error {
	return fmt.Errorf("AST construction error: In function: %s, expected %s for %s. got: %T", function, expected, variable, got)
}

func (c Configuration) TokenLiteral() string { return "Configuration" }

func NewConfiguration(testDefinitions, globalDefinitions Attribute) (Configuration, error) {
	t, ok := testDefinitions.([]Definition)
	if !ok {
		return Configuration{}, astError("NewConfiguration", "[]Definition", "testDefinitions", testDefinitions)
	}

	g, ok := globalDefinitions.([]Definition)
	if !ok {
		return Configuration{}, astError("NewConfiguration", "[]Definition", "globalDefinitions", globalDefinitions)
	}

	return Configuration{TestDefinitions: t, GlobalDefinitions: g}, nil
}

func (td TestDefinition) definitionNode()      {}
func (td TestDefinition) TokenLiteral() string { return "TestDefinition" }

func NewTestDefinition(name, givenBlock, callBlock, thenBlock Attribute) (TestDefinition, error) {
	n, ok := name.(*token.Token)
	if !ok {
		return TestDefinition{}, astError("NewTestDefinition", "*token.Token", "name", name)
	}

	g, ok := givenBlock.(GivenBlock)
	if !ok {
		return TestDefinition{}, astError("NewTestDefinition", "GivenBlock", "givenBlock", givenBlock)
	}

	c, ok := callBlock.(CallBlock)
	if !ok {
		return TestDefinition{}, astError("NewTestDefinition", "CallBlock", "callBlock", callBlock)
	}

	t, ok := thenBlock.(ThenBlock)
	if !ok {
		return TestDefinition{}, astError("NewTestDefinition", "ThenBlock", "thenBlock", thenBlock)
	}

	return TestDefinition{Name: StringLiteral{Value: n.StringValue()}, GivenBlock: g, CallBlock: c, ThenBlock: t}, nil
}

func NewTestDefinitionList() ([]Definition, error) {
	return []Definition{}, nil
}

func AppendTestDefinition(testDefinitions, testDefinition Attribute) ([]Definition, error) {
	ts, ok := testDefinitions.([]Definition)
	if !ok {
		return nil, astError("AppendTestDefinition", "[]Definition", "testDefinitions", testDefinitions)
	}

	t, ok := testDefinition.(TestDefinition)
	if !ok {
		return nil, astError("AppendTestDefinition", "TestDefinition", "testDefinition", testDefinition)
	}

	ts = append(ts, t)

	return ts, nil
}

func (gd GlobalDefinition) definitionNode()      {}
func (gd GlobalDefinition) TokenLiteral() string { return "GlobalDefinition" }

func NewGlobalDefinition(expression Attribute) (GlobalDefinition, error) {
	e, ok := expression.(Expression)
	if !ok {
		return GlobalDefinition{}, astError("NewGlobalDefinition", "Expression", "expression", expression)
	}

	return GlobalDefinition{Expression: e}, nil
}

func NewGlobalDefinitionList() ([]Definition, error) {
	return []Definition{}, nil
}

func AppendGlobalDefinition(globalDefinitions, globalDefinition Attribute) ([]Definition, error) {
	gs, ok := globalDefinitions.([]Definition)
	if !ok {
		return nil, astError("AppendGlobalDefinition", "[]Definition", "globalDefinitions", globalDefinitions)
	}

	g, ok := globalDefinition.(GlobalDefinition)
	if !ok {
		return nil, astError("AppendGlobalDefinition", "GlobalDefinition", "globalDefinition", globalDefinition)
	}

	gs = append(gs, g)

	return gs, nil
}

func (gb GivenBlock) expressionNode()      {}
func (gb GivenBlock) TokenLiteral() string { return gb.Token.StringValue() }

func NewGivenBlock(givenExpressions Attribute) (GivenBlock, error) {
	if givenExpressions == nil {
		return GivenBlock{}, nil
	}

	gs, ok := givenExpressions.([]DefinitionExpression)
	if !ok {
		return GivenBlock{}, astError("NewGivenBlock", "[]DefinitionExpression", "givenExpressions", givenExpressions)
	}

	return GivenBlock{Expressions: gs}, nil
}

func NewGivenExpressionList(attr Attribute) ([]DefinitionExpression, error) {
	list := []DefinitionExpression{}
	if attr != nil {
		t, ok := attr.(DefinitionExpression)
		if !ok {
			return nil, astError("NewGivenExpressionList", "DefinitionExpression", "attr", attr)
		}

		list = append(list, t)
	}

	return list, nil
}

func AppendGivenExpression(givenExpressions, givenExpression Attribute) ([]DefinitionExpression, error) {
	gs, ok := givenExpressions.([]DefinitionExpression)
	if !ok {
		return nil, astError("AppendGivenExpression", "[]DefinitionExpression", "givenExpressions", givenExpressions)
	}

	ge, ok := givenExpression.(DefinitionExpression)
	if !ok {
		return nil, astError("AppendGivenExpression", "DefinitionExpression", "givenExpression", givenExpression)
	}

	gs = append(gs, ge)

	return gs, nil
}

func (cb CallBlock) expressionNode()      {}
func (cb CallBlock) TokenLiteral() string { return cb.Token.StringValue() }

func NewCallBlock(function, arguments Attribute) (CallBlock, error) {
	f, ok := function.(*token.Token)
	if !ok {
		return CallBlock{}, astError("NewCallBlock", "*token.Token", "function", function)
	}

	as, ok := arguments.([]Expression)
	if !ok {
		return CallBlock{}, astError("NewCallBlock", "[]Expression", "arguments", arguments)
	}

	return CallBlock{Function: Identifier{Value: f.StringValue()}, Arguments: as}, nil
}

func NewArgumentList(attr Attribute) ([]Expression, error) {
	list := []Expression{}
	if attr != nil {
		t, ok := attr.(Expression)
		if !ok {
			return nil, astError("NewArgumentList", "Expression", "attr", attr)
		}

		list = append(list, t)
	}

	return list, nil
}

func AppendArgument(arguments, argument Attribute) ([]Expression, error) {
	as, ok := arguments.([]Expression)
	if !ok {
		return nil, astError("AppendArgument", "[]Expression", "arguments", arguments)
	}

	a, ok := argument.(Expression)
	if !ok {
		return nil, astError("AppendArgument", "Expression", "argument", argument)
	}

	as = append(as, a)

	return as, nil
}

func (tb ThenBlock) expressionNode()      {}
func (tb ThenBlock) TokenLiteral() string { return tb.Token.StringValue() }

func NewThenBlock(expression Attribute) (ThenBlock, error) {
	e, ok := expression.(Expression)
	if !ok {
		return ThenBlock{}, astError("NewThenBlock", "Expression", "expression", expression)
	}

	return ThenBlock{Expression: e}, nil
}

func (i Identifier) expressionNode()      {}
func (i Identifier) TokenLiteral() string { return i.Token.StringValue() }

func NewIdentifier(value Attribute) (Identifier, error) {
	v, ok := value.(*token.Token)
	if !ok {
		return Identifier{}, astError("NewIdentifier", "*token.Token", "value", value)
	}

	return Identifier{Value: v.StringValue()}, nil
}

func (il IntegerLiteral) expressionNode()      {}
func (il IntegerLiteral) TokenLiteral() string { return il.Token.StringValue() }

func NewIntegerLiteral(value Attribute) (IntegerLiteral, error) {
	v, ok := value.(*token.Token)
	if !ok {
		return IntegerLiteral{}, astError("NewIntegerLiteral", "*token.Token", "value", value)
	}

	i, err := strconv.Atoi(string(v.Lit))
	if err != nil {
		return IntegerLiteral{}, astError("NewIntegerLiteral", "int", "value", value)
	}

	return IntegerLiteral{Value: i}, nil
}

func (sl StringLiteral) expressionNode()      {}
func (sl StringLiteral) TokenLiteral() string { return sl.Token.StringValue() }

func NewStringLiteral(value Attribute) (StringLiteral, error) {
	v, ok := value.(*token.Token)
	if !ok {
		return StringLiteral{}, astError("NewStringLiteral", "*token.Token", "value", value)
	}

	return StringLiteral{Token: v, Value: v.StringValue()}, nil
}

func (toe TestOperationExpression) expressionNode()      {}
func (toe TestOperationExpression) TokenLiteral() string { return toe.Token.StringValue() }

func NewTestOperationExpressionStringLiteral(testOperation, operation, value Attribute) (TestOperationExpression, error) {
	t, ok := testOperation.(*token.Token)
	if !ok {
		return TestOperationExpression{}, astError("NewTestOperationExpressionStringLiteral", "*token.Token", "testOperation", testOperation)
	}

	o, ok := operation.(*token.Token)
	if !ok {
		return TestOperationExpression{}, astError("NewTestOperationExpressionStringLiteral", "*token.Token", "operation", operation)
	}

	v, ok := value.(*token.Token)
	if !ok {
		return TestOperationExpression{}, astError("NewTestOperationExpressionStringLiteral", "*token.Token", "value", value)
	}

	return TestOperationExpression{TestOperation: t.StringValue(), Operation: o.StringValue(), Value: StringLiteral{Value: v.StringValue()}}, nil
}

func NewTestOperationExpressionIntegerLiteral(testOperation, operation, value Attribute) (TestOperationExpression, error) {
	t, ok := testOperation.(*token.Token)
	if !ok {
		return TestOperationExpression{}, astError("NewTestOperationExpressionIntegerLiteral", "*token.Token", "testOperation", testOperation)
	}

	o, ok := operation.(*token.Token)
	if !ok {
		return TestOperationExpression{}, astError("NewTestOperationExpressionIntegerLiteral", "*token.Token", "operation", operation)
	}

	v, ok := value.(*token.Token)
	if !ok {
		return TestOperationExpression{}, astError("NewTestOperationExpressionIntegerLiteral", "*token.Token", "value", value)
	}

	i, err := NewIntegerLiteral(v)
	if err != nil {
		return TestOperationExpression{}, err
	}

	return TestOperationExpression{TestOperation: t.StringValue(), Operation: o.StringValue(), Value: i}, nil
}

func NewTestOperationExpressionIdentifier(testOperation, operation, value Attribute) (TestOperationExpression, error) {
	t, ok := testOperation.(*token.Token)
	if !ok {
		return TestOperationExpression{}, astError("NewTestOperationExpressionIdentifier", "*token.Token", "testOperation", testOperation)
	}

	o, ok := operation.(*token.Token)
	if !ok {
		return TestOperationExpression{}, astError("NewTestOperationExpressionIdentifier", "*token.Token", "operation", operation)
	}

	v, ok := value.(*token.Token)
	if !ok {
		return TestOperationExpression{}, astError("NewTestOperationExpressionIdentifier", "*token.Token", "value", value)
	}

	i, err := NewIdentifier(v)
	if err != nil {
		return TestOperationExpression{}, err
	}

	return TestOperationExpression{TestOperation: t.StringValue(), Operation: o.StringValue(), Value: i}, nil
}

func (de DefinitionExpression) expressionNode()      {}
func (de DefinitionExpression) TokenLiteral() string { return de.Token.StringValue() }

func NewDefinitionExpression(value, id Attribute) (DefinitionExpression, error) {
	v, ok := value.(Expression)
	if !ok {
		return DefinitionExpression{}, astError("NewDefinitionExpression", "Expression", "value", value)
	}

	i, ok := id.(*token.Token)
	if !ok {
		return DefinitionExpression{}, astError("NewDefinitionExpression", "*token.Token", "id", id)
	}

	return DefinitionExpression{Value: v, Id: Identifier{Value: i.StringValue()}}, nil
}

func (o Object) expressionNode()      {}
func (o Object) TokenLiteral() string { return o.Token.StringValue() }

func NewObject(name, properties Attribute) (Object, error) {
	n, ok := name.(*token.Token)
	if !ok {
		return Object{}, astError("NewObject", "*token.Token", "name", name)
	}

	p, ok := properties.([]ObjectProperty)
	if !ok {
		return Object{}, astError("NewObject", "[]ObjectProperty", "properties", properties)
	}

	return Object{Name: Identifier{Value: n.StringValue()}, Properties: p}, nil
}

func NewObjectPropertyStringLiteral(key, value Attribute) (ObjectProperty, error) {
	k, ok := key.(*token.Token)
	if !ok {
		return ObjectProperty{}, astError("NewObjectProperty", "*token.Token", "key", key)
	}

	v, ok := value.(*token.Token)
	if !ok {
		return ObjectProperty{}, astError("NewObjectProperty", "Expression", "value", value)
	}

	return ObjectProperty{Key: k.StringValue(), Value: StringLiteral{Value: v.StringValue()}}, nil
}

func NewObjectPropertyIntegerLiteral(key, value Attribute) (ObjectProperty, error) {
	k, ok := key.(*token.Token)
	if !ok {
		return ObjectProperty{}, astError("NewObjectProperty", "*token.Token", "key", key)
	}

	v, ok := value.(*token.Token)
	if !ok {
		return ObjectProperty{}, astError("NewObjectProperty", "*token.Token", "value", value)
	}

	i, err := NewIntegerLiteral(v)
	if err != nil {
		return ObjectProperty{}, err
	}

	return ObjectProperty{Key: k.StringValue(), Value: i}, nil
}

func NewObjectPropertyList(attr Attribute) ([]ObjectProperty, error) {
	list := []ObjectProperty{}
	if attr != nil {
		t, ok := attr.(ObjectProperty)
		if !ok {
			return nil, astError("NewObjectPropertyList", "ObjectProperty", "attr", attr)
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

	os = append(os, o)

	return os, nil
}
