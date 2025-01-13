package main

import (
	"testing"

	"github.com/Siposattila/TestMe/tmtsl/lexer"
	"github.com/Siposattila/TestMe/tmtsl/token"
)

func TestToken(t *testing.T) {
	type Test struct {
		expectedType    token.Type
		expectedLiteral string
	}
	const input = `
			/* comment */
            TEST "Example"
                CALL "Bark"()
                THEN OUTPUT EQUALS "WAU";
			`

	tests := []Test{
		{token.TokMap.Type("test"), "TEST"},
		{token.TokMap.Type("string_literal"), "\"Example\""},
		{token.TokMap.Type("call"), "CALL"},
		{token.TokMap.Type("string_literal"), "\"Bark\""},
		{token.TokMap.Type("lparen"), "("},
		{token.TokMap.Type("rparen"), ")"},
		{token.TokMap.Type("then"), "THEN"},
		{token.TokMap.Type("output"), "OUTPUT"},
		{token.TokMap.Type("equals"), "EQUALS"},
		{token.TokMap.Type("string_literal"), "\"WAU\""},
		{token.TokMap.Type("semicolon"), ";"},
	}

	l := lexer.NewLexer([]byte(input))
	for i, tt := range tests {
		tok := l.Scan()

		if tok.Type != tt.expectedType {
			t.Fatalf("tests[%d] - tokentype wrong. expected='%s', got='%s' at line %d, column %d",
				i, token.TokMap.Id(tt.expectedType), token.TokMap.Id(tok.Type), tok.Pos.Line, tok.Pos.Column)
		}

		if string(tok.Lit) != tt.expectedLiteral {
			t.Fatalf("tests[%d] - literal wrong. expected='%q', got='%q' at line %d, column %d",
				i, tt.expectedLiteral, string(tok.Lit), tok.Pos.Line, tok.Pos.Column)
		}
	}
}
