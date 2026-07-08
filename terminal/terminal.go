package terminal

import (
	"context"
	"log"

	"github.com/mum4k/termdash"
	"github.com/mum4k/termdash/container"
	"github.com/mum4k/termdash/keyboard"
	"github.com/mum4k/termdash/terminal/tcell"
	"github.com/mum4k/termdash/terminal/terminalapi"
)

func StartTerminal() (*tcell.Terminal, *container.Container, context.Context, context.CancelFunc) {
	// Initialise Tcell
	// This takes over the full screen and hides the standard terminal interface.
	terminal, err := tcell.New()
	if err != nil {
		log.Fatalf("Terminal initialisation failed: %v", err)
	}

	// Root Container
	rootContainer, err := container.New(terminal, container.ID("root"))
	if err != nil {
		log.Fatalf("Container initialisation failed: %v", err)
	}

	appContext, cancel := context.WithCancel(context.Background())

	return terminal, rootContainer, appContext, cancel
}

func Run(ctx context.Context, cancel context.CancelFunc, terminal *tcell.Terminal, rootContainer *container.Container) {
	defer terminal.Close()
	defer cancel()

	quitter := func(k *terminalapi.Keyboard) {
		if k.Key == keyboard.KeyCtrlC {
			cancel()
		}
	}

	if err := termdash.Run(ctx, terminal, rootContainer, termdash.KeyboardSubscriber(quitter)); err != nil {
		log.Fatalf("Termdash run failed: %v", err)
	}
}

func LoadLayout(rootContainer *container.Container, layout string, elements [][]container.Option) {
	var opts []container.Option

	if layout == "split" && len(elements) >= 2 {
		opts = buildSplitLayout(elements[0], elements[1])
	} else if len(elements) > 0 {
		// Fallback to a simple full-screen layout
		opts = elements[0]
	}

	if err := rootContainer.Update("root", opts...); err != nil {
		log.Printf("Failed to update layout: %v", err)
	}
}
