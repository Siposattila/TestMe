package generator

import (
	"bytes"
	"fmt"

	"github.com/Siposattila/TestMe/tmtsl/ast"
)

func write(buffer *bytes.Buffer, code string, arguments ...interface{}) {
	buffer.WriteString(fmt.Sprintf(code, arguments...))
}

func Generator(c *ast.Configuration) bytes.Buffer {
	var buffer bytes.Buffer
	generate(c, &buffer)

	return buffer
}

func generate(node ast.Node, buffer *bytes.Buffer) string {
	switch node := node.(type) {
	case *ast.Configuration:
		return generateConfiguration(node, buffer)
	case ast.GlobalDefinition:
		return ""
	case ast.TestDefinition:
		return generateTestDefinition(node, buffer)
	case ast.GivenBlock:
		return generateGivenBlock(node, buffer)
	case ast.CallBlock:
		return generateCallBlock(node, buffer)
	case ast.ThenBlock:
		return generateThenBlock(node, buffer)
	case ast.Object:
		return ""
	case ast.ObjectProperty:
		return ""
	case ast.TestOperationExpression:
		return generateTestOperationExpression(node, buffer)
	case ast.DefinitionExpression:
		return generateDefinitionExpression(node, buffer)
	case ast.StringLiteral:
		return generateStringLiteral(node, buffer)
	case ast.IntegerLiteral:
		return generateIntegerLiteral(node, buffer)
	}

	return ""
}
