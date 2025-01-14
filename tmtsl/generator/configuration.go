package generator

import (
	"bytes"

	"github.com/Siposattila/TestMe/tmtsl/ast"
)

func generateConfiguration(node *ast.Configuration, buffer *bytes.Buffer) string {
	write(buffer, "namespace XY\n{\n\tpublic class TestXY\n\t{\n")

	for _, testDef := range node.TestDefinitions {
		generate(testDef, buffer)
	}

	write(buffer, "\t}\n}")

	return ""
}
