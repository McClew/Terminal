package elements

import (
	"context"
	"math/rand"
	"strings"
	"time"

	"github.com/mum4k/termdash/widgets/text"
)

func NewSignalLoss() (*text.Text, error) {
	txt, err := text.New()
	if err != nil {
		return nil, err
	}

	go func() {
		frame := 0
		ticker := time.NewTicker(50 * time.Millisecond)
		defer ticker.Stop()

		for {
			select {
			case <-ticker.C:
				// Use a fixed generic size. The text widget will clip anything out of bounds.
				glitch := renderGlitch(frame, 80, 24)
				txt.Reset()
				txt.Write(glitch)
				frame++
			case <-context.Background().Done():
				return
			}
		}
	}()

	return txt, nil
}

func renderGlitch(frame, width, height int) string {
	var sb strings.Builder

	staticPool := []rune{'░', '▒', '▓', '█', ' ', '▖', '▗', '▘', '▙', '▚', '▛', '▜'}

	if height <= 0 {
		height = 20
	}
	if width <= 0 {
		width = 60
	}

	midY := height / 2

	for y := 0; y < height; y++ {
		isGlitchRow := (y+frame)%7 == 0 && rand.Float32() > 0.4

		for x := 0; x < width; x++ {
			if y == midY && x > (width/2)-10 && x < (width/2)+10 {
				textStr := "  NO SIGNAL  "
				charIdx := x - ((width / 2) - 10)

				if charIdx >= 0 && charIdx < len(textStr) {
					if isGlitchRow && rand.Float32() > 0.5 {
						sb.WriteRune(staticPool[rand.Intn(len(staticPool))])
					} else {
						sb.WriteByte(textStr[charIdx])
					}
					continue
				}
			}

			if isGlitchRow {
				sb.WriteRune('█')
			} else {
				idx := (rand.Intn(len(staticPool)) + frame) % len(staticPool)
				sb.WriteRune(staticPool[idx])
			}
		}
		
		if y < height-1 {
			sb.WriteString("\n")
		}
	}

	return sb.String()
}
