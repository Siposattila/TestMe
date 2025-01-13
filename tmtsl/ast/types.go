package ast

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
