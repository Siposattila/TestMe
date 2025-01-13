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

func NewTestOperationExpressionStringLiteral(testOperation, operation, expression Attribute) (TestOperationExpression, error) {
	t, ok := testOperation.(*token.Token)
	if !ok {
		return TestOperationExpression{}, astError("NewTestOperationExpressionStringLiteral", "*token.Token", "testOperation", testOperation)
	}

	o, ok := operation.(*token.Token)
	if !ok {
		return TestOperationExpression{}, astError("NewTestOperationExpressionStringLiteral", "*token.Token", "operation", operation)
	}

	sl, err := NewStringLiteral(expression)
	if err != nil {
		return TestOperationExpression{}, err
	}

	return TestOperationExpression{Token: t, TestOperation: string(t.Lit), Operation: string(o.Lit), Expression: sl}, nil
}

func NewTestOperationExpressionIntegerLiteral(testOperation, operation, expression Attribute) (TestOperationExpression, error) {
	t, ok := testOperation.(*token.Token)
	if !ok {
		return TestOperationExpression{}, astError("NewTestOperationExpressionIntegerLiteral", "*token.Token", "testOperation", testOperation)
	}

	o, ok := operation.(*token.Token)
	if !ok {
		return TestOperationExpression{}, astError("NewTestOperationExpressionIntegerLiteral", "*token.Token", "operation", operation)
	}

	il, err := NewIntegerLiteral(expression)
	if err != nil {
		return TestOperationExpression{}, err
	}

	return TestOperationExpression{Token: t, TestOperation: string(t.Lit), Operation: string(o.Lit), Expression: il}, nil
}
