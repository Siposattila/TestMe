package generator

import (
	"bytes"
	"strings"

	"github.com/Siposattila/TestMe/tmtsl/ast"
)

func generateStringLiteral(node ast.StringLiteral, buffer *bytes.Buffer) string {
	write(buffer, "%s", node.Value)

	return ""
}

func generateIntegerLiteral(node ast.IntegerLiteral, buffer *bytes.Buffer) string {
	write(buffer, "%s", strings.ReplaceAll(node.Value, "\"", ""))

	return ""
}
