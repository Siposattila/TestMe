package ast

import "github.com/Siposattila/TestMe/tmtsl/token"

type Attribute interface{}

type Node interface {
	TokenLiteral() string
}

type Definition interface {
	Node
	definitionNode()
}

type Expression interface {
	Node
	expressionNode()
}

type Configuration struct {
	TestDefinitions   []Definition `json:"testDefinitions"`
	GlobalDefinitions []Definition `json:"globalDefinitions"`
}

type TestDefinition struct {
	Token      *token.Token `json:"-"`
	Name       Expression   `json:"name"`
	GivenBlock GivenBlock   `json:"givenBlock,omitempty"`
	CallBlock  CallBlock    `json:"callBlock"`
	ThenBlock  ThenBlock    `json:"thenBlock"`
}

type GlobalDefinition struct {
	Token      *token.Token `json:"-"`
	Expression Expression   `json:"expression"`
}

type Identifier struct {
	Token *token.Token `json:"-"`
	Value string       `json:"value"`
}

type IntegerLiteral struct {
	Token *token.Token `json:"-"`
	Value int          `json:"value"`
}

type StringLiteral struct {
	Token *token.Token `json:"-"`
	Value string       `json:"value"`
}

type TestOperationExpression struct {
	Token         *token.Token `json:"-"`
	TestOperation string       `json:"testOperation"`
	Operation     string       `json:"operation"`
	Value         Expression   `json:"value"`
}

type DefinitionExpression struct {
	Token *token.Token `json:"-"`
	Value Expression   `json:"value"`
	Id    Identifier   `json:"identifier"`
}

type GivenBlock struct {
	Token       *token.Token           `json:"-"`
	Expressions []DefinitionExpression `json:"expressions"`
}

type CallBlock struct {
	Token     *token.Token `json:"-"`
	Function  Identifier   `json:"function"`
	Arguments []Expression `json:"arguments,omitempty"`
}

type ThenBlock struct {
	Token      *token.Token `json:"-"`
	Expression Expression   `json:"expression"`
}

type Object struct {
	Token      *token.Token     `json:"-"`
	Name       Identifier       `json:"name"`
	Properties []ObjectProperty `json:"properties,omitempty"`
}

type ObjectProperty struct {
	Token *token.Token `json:"-"`
	Key   string       `json:"key"`
	Value Expression   `json:"value"` // Can be StringLiteral or IntegerLiteral.
}
