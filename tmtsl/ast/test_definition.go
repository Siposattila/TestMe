package ast

import "github.com/Siposattila/TestMe/tmtsl/token"

type TestDefinition struct {
	Name       string     `json:"name"`
	GivenBlock GivenBlock `json:"givenBlock,omitempty"`
	CallBlock  CallBlock  `json:"callBlock"`
	ThenBlock  ThenBlock  `json:"thenBlock"`
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

	return TestDefinition{Name: n.StringValue(), GivenBlock: g, CallBlock: c, ThenBlock: t}, nil
}
