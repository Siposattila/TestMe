package main

import (
	"fmt"
	"os"
	"path/filepath"

	"github.com/Siposattila/TestMe/tmtsl/ast"
	"github.com/Siposattila/TestMe/tmtsl/checker"
	"github.com/Siposattila/TestMe/tmtsl/generator"
	"github.com/Siposattila/TestMe/tmtsl/lexer"
	"github.com/Siposattila/TestMe/tmtsl/parser"
)

func parse(input string) *ast.Configuration {
	l := lexer.NewLexer([]byte(input))
	p := parser.NewParser()

	root, err := p.Parse(l)
	if err != nil {
		panic(err)
	}

	c, _ := root.(*ast.Configuration)

	return c
}

func main() {
	if len(os.Args) < 2 {
		panic("no valid file name or path provided provided for a tmtsl file!")
	}

	path, _ := filepath.Abs(os.Args[len(os.Args)-1])
	input, err := os.ReadFile(path)
	if err != nil {
		panic(err)
	}

	c := parse(string(input))

	err = checker.Checker(c)
	if err != nil {
		panic(err)
	}

	b := generator.Generator(c)
	fmt.Println(b.String())
}
