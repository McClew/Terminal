package scenes

import (
	"context"
	"log"

	"Terminal/terminal"

	"github.com/mum4k/termdash/align"
	"github.com/mum4k/termdash/container"
	"github.com/mum4k/termdash/container/grid"
	"github.com/mum4k/termdash/terminal/tcell"
	"github.com/mum4k/termdash/widgets/button"
	"github.com/mum4k/termdash/widgets/text"
)

func RunMainMenu(term *tcell.Terminal, rootContainer *container.Container) string {
	ctx, cancel := context.WithCancel(context.Background())

	var nextScene string

	title, _ := text.New()
	title.Write("MAIN MENU")

	startButton, _ := button.New(
		"Enter Terminal",
		func() error {
			nextScene = "proto"
			cancel()
			return nil
		},
		button.DisableShadow(),
		button.Width(20),
		button.Height(3),
	)

	settingsButton, _ := button.New(
		"Settings",
		func() error {
			return nil
		},
		button.DisableShadow(),
		button.Width(20),
		button.Height(3),
	)

	exitButton, _ := button.New(
		"Exit",
		func() error {
			nextScene = "exit"
			cancel()
			return nil
		},
		button.DisableShadow(),
		button.Width(20),
		button.Height(3),
	)

	builder := grid.New()
	builder.Add(
		grid.RowHeightPerc(10),
		grid.RowHeightPerc(10,
			grid.Widget(title,
				container.AlignHorizontal(align.HorizontalCenter),
				container.AlignVertical(align.VerticalMiddle),
			),
		),
		grid.RowHeightPerc(20,
			grid.Widget(startButton,
				container.AlignHorizontal(align.HorizontalCenter),
				container.AlignVertical(align.VerticalMiddle),
			),
		),
		grid.RowHeightPerc(20,
			grid.Widget(settingsButton,
				container.AlignHorizontal(align.HorizontalCenter),
				container.AlignVertical(align.VerticalMiddle),
			),
		),
		grid.RowHeightPerc(20,
			grid.Widget(exitButton,
				container.AlignHorizontal(align.HorizontalCenter),
				container.AlignVertical(align.VerticalMiddle),
			),
		),
		grid.RowHeightPerc(20),
	)

	menuOpts, err := builder.Build()
	if err != nil {
		term.Close()
		log.Fatalf("Failed to build menu layout: %v", err)
	}

	terminal.LoadLayout(rootContainer, "full", [][]container.Option{menuOpts})

	terminal.Run(ctx, cancel, term, rootContainer)
	return nextScene
}
