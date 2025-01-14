package checker

import "github.com/Siposattila/TestMe/tmtsl/ast"

func Checker(c *ast.Configuration) error {
	_, err := check(c)

	return err
}

func check(node ast.Node) (string, error) {
	//switch node := node.(type) {
	//}

	return "", nil
}
