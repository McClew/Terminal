package scenes

import (
	"context"
	"log"

	"Terminal/elements"
	"Terminal/terminal"

	"github.com/mum4k/termdash/container"
	"github.com/mum4k/termdash/linestyle"
	"github.com/mum4k/termdash/terminal/tcell"
)

func RunProto(term *tcell.Terminal, rootContainer *container.Container) string {
	ctx, cancel := context.WithCancel(context.Background())
	nextScene := "exit" // Default to exit when Ctrl+C is pressed

	_, terminalOpts, err := elements.NewTerminal()
	if err != nil {
		log.Fatalf("Failed to create terminal: %v", err)
	}

	/*
		radarWidget, err := elements.NewRadar()
		if err != nil {
			log.Fatalf("Failed to create radar: %v", err)
		}

		sideAreaOpts := []container.Option{
			container.Border(linestyle.Light),
			container.BorderTitle("RADAR"),
			container.PlaceWidget(radarWidget),
		}
	*/

	signalLossWidget, err := elements.NewSignalLoss()
	if err != nil {
		log.Fatalf("Failed to create signal loss: %v", err)
	}

	sideAreaOpts := []container.Option{
		container.Border(linestyle.Light),
		container.BorderTitle("SIGNAL LOSS"),
		container.PlaceWidget(signalLossWidget),
	}

	elements := [][]container.Option{terminalOpts, sideAreaOpts}
	terminal.LoadLayout(rootContainer, "split", elements)

	terminal.Run(ctx, cancel, term, rootContainer)
	return nextScene
}
