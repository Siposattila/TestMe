package ast

import "github.com/Siposattila/TestMe/tmtsl/token"

type Attribute interface{}

type Configuration struct {
	Definitions []Definition
}

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

type GlobalDefinition struct {
	Token *token.Token  `json:"-"`
	Name  StringLiteral `json:"name"`
	Id    Identifier    `json:"identifier"`
}

// Expressions
type Identifier struct {
	Token *token.Token `json:"-"`
	Value string       `json:"value"`
}

type IntegerLiteral struct {
	Token *token.Token `json:"-"`
	Value string       `json:"value"`
}

type StringLiteral struct {
	Token *token.Token `json:"-"`
	Value string       `json:"value"`
}

type TestOperationExpression struct {
	Token         *token.Token `json:"-"`
	TestOperation string       `json:"testOperation"`
	Operation     string       `json:"operation"`
	Exp           Expression   `json:"expression"`
}
