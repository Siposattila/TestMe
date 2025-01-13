package ast

import "github.com/Siposattila/TestMe/tmtsl/token"

type IntegerLiteral struct {
	Token *token.Token `json:"-"`
	Value string       `json:"value"`
}

type StringLiteral struct {
	Token *token.Token `json:"-"`
	Value string       `json:"value"`
}

func (il IntegerLiteral) expressionNode()      {}
func (il IntegerLiteral) TokenLiteral() string { return string(il.Token.Lit) }

func NewIntegerLiteral(value Attribute) (IntegerLiteral, error) {
	v, ok := value.(*token.Token)
	if !ok {
		return IntegerLiteral{}, astError("NewIntegerLiteral", "*token.Token", "value", value)
	}

	return IntegerLiteral{Token: v, Value: string(v.Lit)}, nil
}

func (sl StringLiteral) expressionNode()      {}
func (sl StringLiteral) TokenLiteral() string { return string(sl.Token.Lit) }

func NewStringLiteral(value Attribute) (StringLiteral, error) {
	v, ok := value.(*token.Token)
	if !ok {
		return StringLiteral{}, astError("NewStringLiteral", "*token.Token", "value", value)
	}

	return StringLiteral{Token: v, Value: string(v.Lit)}, nil
}
