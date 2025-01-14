package generator

import (
	"bytes"
	"strings"

	"github.com/Siposattila/TestMe/tmtsl/ast"
)

func generateCallBlock(node ast.CallBlock, buffer *bytes.Buffer) string {
	write(buffer, "\t\t\tvar result = %s(", strings.ReplaceAll(node.Function.Value, "\"", ""))

	for i, arg := range node.Arguments {
		generate(arg, buffer)

		if i != 0 && i < len(node.Arguments) {
			write(buffer, ", ")
		}
	}

	write(buffer, ");\n")

	return ""
}
