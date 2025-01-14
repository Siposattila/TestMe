package generator

import (
	"bytes"

	"github.com/Siposattila/TestMe/tmtsl/ast"
)

func generateGivenBlock(node ast.GivenBlock, buffer *bytes.Buffer) string {
	for _, defExpr := range node.Expressions {
		generate(defExpr, buffer)
	}

	return ""
}
