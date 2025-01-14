package generator

import (
	"bytes"
	"strings"

	"github.com/Siposattila/TestMe/tmtsl/ast"
)

func generateTestDefinition(node ast.TestDefinition, buffer *bytes.Buffer) string {
	write(buffer, "\t\t[Test]\n\t\tpublic void %s()\n\t\t{\n", strings.ReplaceAll(node.Name.Value, "\"", ""))

	generate(node.GivenBlock, buffer)
	generate(node.CallBlock, buffer)
	generate(node.ThenBlock, buffer)

	write(buffer, "\t\t}\n\n")

	return ""
}
