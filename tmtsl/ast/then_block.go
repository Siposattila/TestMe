package ast

type ThenBlock struct {
	Expression Expression `json:"expression"`
}

func (tb ThenBlock) expressionNode()      {}
func (tb ThenBlock) TokenLiteral() string { return tb.Expression.TokenLiteral() }

func NewThenBlock(expression Attribute) (ThenBlock, error) {
	e, ok := expression.(Expression)
	if !ok {
		return ThenBlock{}, astError("NewThenBlock", "Expression", "expression", expression)
	}

	return ThenBlock{Expression: e}, nil
}
