package terminal

import (
	"github.com/mum4k/termdash/container"
)

// Layouts
// 1. "full" - Full-screen elements like a map, terminal or menu
// 2. "split" - 80/20 vertical split, main container takes up 80% of the screen, side container takes up 20%
// 3. "dual" - 50/50 split, useful for side-by-side comparisons
// 4. "quad" - 50/50 split, useful for side-by-side comparisons

func buildFullLayout(containerOptions []container.Option) []container.Option {
	return containerOptions
}

func buildSplitLayout(mainAreaOptions, sideAreaOptions []container.Option) []container.Option {
	return []container.Option{
		container.SplitVertical(
			container.Left(
				mainAreaOptions...),
			container.Right(
				sideAreaOptions...),
			container.SplitPercent(70),
		),
	}
}
