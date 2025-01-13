package ast

type GlobalDefinition struct {
	Expression Expression `json:"expression"`
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
