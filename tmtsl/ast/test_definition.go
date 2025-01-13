package ast

type TestDefinition struct {
	Name       StringLiteral `json:"name"`
	GivenBlock GivenBlock    `json:"givenBlock,omitempty"`
	CallBlock  CallBlock     `json:"callBlock"`
	ThenBlock  ThenBlock     `json:"thenBlock"`
}

func (td TestDefinition) definitionNode()      {}
func (td TestDefinition) TokenLiteral() string { return "TestDefinition" }

func NewTestDefinition(name, givenBlock, callBlock, thenBlock Attribute) (TestDefinition, error) {
	n, ok := name.(StringLiteral)
	if !ok {
		return TestDefinition{}, astError("NewTestDefinition", "StringLiteral", "name", name)
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

	return TestDefinition{Name: n, GivenBlock: g, CallBlock: c, ThenBlock: t}, nil
}
