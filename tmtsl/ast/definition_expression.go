package ast

import "github.com/Siposattila/TestMe/tmtsl/token"

type DefinitionExpression struct {
	Token *token.Token  `json:"-"`
	Value Expression    `json:"value"`
	Name  StringLiteral `json:"name"`
}

func (de DefinitionExpression) expressionNode()      {}
func (de DefinitionExpression) TokenLiteral() string { return de.Token.StringValue() }

func NewDefinitionExpression(value, name Attribute) (DefinitionExpression, error) {
	v, ok := value.(Expression)
	if !ok {
		return DefinitionExpression{}, astError("NewDefinitionExpression", "Expression", "value", value)
	}

	n, ok := name.(StringLiteral)
	if !ok {
		return DefinitionExpression{}, astError("NewDefinitionExpression", "StringLiteral", "name", name)
	}

	return DefinitionExpression{Token: n.Token, Value: v, Name: n}, nil
}
