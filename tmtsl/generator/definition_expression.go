package generator

import (
	"bytes"
	"strings"

	"github.com/Siposattila/TestMe/tmtsl/ast"
)

func generateDefinitionExpression(node ast.DefinitionExpression, buffer *bytes.Buffer) string {
	write(buffer, "\t\t\t")
	switch node.Value.(type) {
	case ast.StringLiteral:
		write(buffer, "string")
	case ast.IntegerLiteral:
		write(buffer, "int")
	}

	write(buffer, " %s = ", strings.ReplaceAll(node.Name.Value, "\"", ""))
	generate(node.Value, buffer)
	write(buffer, ";\n")

	return ""
}
