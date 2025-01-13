package ast

type Configuration struct {
	TestDefinitions   []Definition `json:"testDefinitions"`
	GlobalDefinitions []Definition `json:"globalDefinitions"`
}

func (c Configuration) TokenLiteral() string { return "Configuration" }

func NewConfiguration(testDefinitions, globalDefinitions Attribute) (*Configuration, error) {
	t, ok := testDefinitions.([]Definition)
	if !ok {
		return nil, astError("NewConfiguration", "[]Definition", "testDefinitions", testDefinitions)
	}

	g, ok := globalDefinitions.([]Definition)
	if !ok {
		return nil, astError("NewConfiguration", "[]Definition", "globalDefinitions", globalDefinitions)
	}

	return &Configuration{TestDefinitions: t, GlobalDefinitions: g}, nil
}
