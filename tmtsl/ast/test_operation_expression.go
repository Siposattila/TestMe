package ast

import "github.com/Siposattila/TestMe/tmtsl/token"

type TestOperationExpression struct {
	Token         *token.Token `json:"-"`
	TestOperation string       `json:"testOperation"`
	Operation     string       `json:"operation"`
	Expression    Expression   `json:"expression"`
}

func (toe TestOperationExpression) expressionNode()      {}
func (toe TestOperationExpression) TokenLiteral() string { return string(toe.Token.Lit) }

func NewTestOperationExpression(testOperation, operation, expression Attribute) (TestOperationExpression, error) {
	t, ok := testOperation.(*token.Token)
	if !ok {
		return TestOperationExpression{}, astError("NewTestOperationExpression", "*token.Token", "testOperation", testOperation)
	}

	o, ok := operation.(*token.Token)
	if !ok {
		return TestOperationExpression{}, astError("NewTestOperationExpression", "*token.Token", "operation", operation)
	}

	e, ok := expression.(Expression)
	if !ok {
		return TestOperationExpression{}, astError("NewTestOperationExpression", "Expression", "expression", expression)
	}

	return TestOperationExpression{Token: t, TestOperation: string(t.Lit), Operation: string(o.Lit), Expression: e}, nil
}
