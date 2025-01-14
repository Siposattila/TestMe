package generator

import (
	"bytes"
	"strings"

	"github.com/Siposattila/TestMe/tmtsl/ast"
)

func generateTestOperationExpression(node ast.TestOperationExpression, buffer *bytes.Buffer) string {
	write(buffer, "\t\t\tAssert.That(result, Is.EqualTo(")
	switch node := node.Expression.(type) {
	case ast.StringLiteral:
		write(buffer, "%s", node.Value)
	case ast.IntegerLiteral:
		write(buffer, "%s", strings.ReplaceAll(node.Value, "\"", ""))
	}
	write(buffer, "));\n")

	return ""
}
