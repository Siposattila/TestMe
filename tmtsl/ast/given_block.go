package ast

import "github.com/Siposattila/TestMe/tmtsl/token"

type GivenBlock struct {
	Token       *token.Token           `json:"-"`
	Expressions []DefinitionExpression `json:"expressions"`
}

func (gb GivenBlock) expressionNode()      {}
func (gb GivenBlock) TokenLiteral() string { return string(gb.Token.Lit) }

func NewGivenBlock(expressions Attribute) (GivenBlock, error) {
	if expressions == nil {
		return GivenBlock{}, nil
	}

	es, ok := expressions.([]DefinitionExpression)
	if !ok {
		return GivenBlock{}, astError("NewGivenBlock", "[]DefinitionExpression", "expressions", expressions)
	}

	return GivenBlock{Expressions: es}, nil
}

func NewGivenExpressionList(expression Attribute) ([]DefinitionExpression, error) {
	list := []DefinitionExpression{}
	if expression != nil {
		e, ok := expression.(DefinitionExpression)
		if !ok {
			return nil, astError("NewGivenExpressionList", "DefinitionExpression", "expression", expression)
		}

		list = append(list, e)
	}

	return list, nil
}

func AppendGivenExpression(expressions, expression Attribute) ([]DefinitionExpression, error) {
	es, ok := expressions.([]DefinitionExpression)
	if !ok {
		return nil, astError("AppendGivenExpression", "[]DefinitionExpression", "expressions", expressions)
	}

	e, ok := expression.(DefinitionExpression)
	if !ok {
		return nil, astError("AppendGivenExpression", "DefinitionExpression", "expression", expression)
	}

	return append(es, e), nil
}
