package generator

import (
	"bytes"

	"github.com/Siposattila/TestMe/tmtsl/ast"
)

func generateThenBlock(node ast.ThenBlock, buffer *bytes.Buffer) string {
	generate(node.Expression, buffer)

	return ""
}
