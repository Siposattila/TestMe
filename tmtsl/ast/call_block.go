package ast

import "github.com/Siposattila/TestMe/tmtsl/token"

type CallBlock struct {
	Token     *token.Token `json:"-"`
	Function  string       `json:"function"`
	Arguments []Expression `json:"arguments"`
}

func (cb CallBlock) expressionNode()      {}
func (cb CallBlock) TokenLiteral() string { return string(cb.Token.Lit) }

func NewCallBlock(function, arguments Attribute) (CallBlock, error) {
	f, ok := function.(*token.Token)
	if !ok {
		return CallBlock{}, astError("NewCallBlock", "*token.Token", "function", function)
	}

	as, ok := arguments.([]Expression)
	if !ok {
		return CallBlock{}, astError("NewCallBlock", "[]Expression", "arguments", arguments)
	}

	return CallBlock{Token: f, Function: string(f.Lit), Arguments: as}, nil
}

func NewArgumentList(expression Attribute) ([]Expression, error) {
	list := []Expression{}
	if expression != nil {
		t, ok := expression.(Expression)
		if !ok {
			return nil, astError("NewArgumentList", "Expression", "expression", expression)
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

	return append(as, a), nil
}
