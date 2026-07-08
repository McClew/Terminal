package elements

import (
	"github.com/mum4k/termdash/container"
	"github.com/mum4k/termdash/linestyle"
	"github.com/mum4k/termdash/widgets/text"
	"github.com/mum4k/termdash/widgets/textinput"
)

// Terminal represents a custom composite component.
type Terminal struct {
	Output *text.Text
	Input  *textinput.TextInput
}

// NewTerminal initialises the custom terminal component.
func NewTerminal() (*Terminal, []container.Option, error) {
	out, err := text.New()
	if err != nil {
		return nil, nil, err
	}

	in, err := textinput.New()
	if err != nil {
		return nil, nil, err
	}

	opts := []container.Option{
		container.Border(linestyle.Light),
		container.BorderTitle("TERMINAL"),
		container.SplitHorizontal(
			container.Top(
				container.PlaceWidget(out),
			),
			container.Bottom(
				container.PlaceWidget(in),
			),
			container.SplitPercent(80),
		),
	}

	return &Terminal{
		Output: out,
		Input:  in,
	}, opts, nil
}
