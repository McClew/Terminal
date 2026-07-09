package elements

import (
	"image"
	"math/rand"
	"strings"

	"github.com/mum4k/termdash/private/canvas"
	"github.com/mum4k/termdash/terminal/terminalapi"
	"github.com/mum4k/termdash/widgetapi"
)

// SignalLoss implements widgetapi.Widget
type SignalLoss struct {
	frame int
}

func NewSignalLoss() (*SignalLoss, error) {
	return &SignalLoss{}, nil
}

// Draw is called by termdash automatically. It provides the exact canvas size.
func (s *SignalLoss) Draw(cvs *canvas.Canvas, meta *widgetapi.Meta) error {
	size := cvs.Size()
	width, height := size.X, size.Y

	// Fetch your dynamically sized glitch frame
	glitch := renderGlitch(s.frame, width, height)

	// Write the string to the canvas line by line
	lines := strings.Split(glitch, "\n")
	for y, line := range lines {
		x := 0
		for _, char := range line {
			if x < width && y < height {
				cvs.SetCell(image.Point{x, y}, char)
			}
			x++
		}
	}

	s.frame++
	return nil
}

// Required interface methods (kept empty as no input is needed)
func (s *SignalLoss) Keyboard(k *terminalapi.Keyboard, meta *widgetapi.EventMeta) error { return nil }
func (s *SignalLoss) Mouse(m *terminalapi.Mouse, meta *widgetapi.EventMeta) error       { return nil }
func (s *SignalLoss) Options() widgetapi.Options             { return widgetapi.Options{} }

// renderGlitch remains identical to your original logic
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
	textStr := "  NO SIGNAL  "
	textLen := len(textStr)
	startX := (width / 2) - (textLen / 2)
	endX := startX + textLen

	for y := 0; y < height; y++ {
		isGlitchRow := (y+frame)%7 == 0 && rand.Float32() > 0.4

		for x := 0; x < width; x++ {
			if y == midY && x >= startX && x < endX {
				charIdx := x - startX

				if isGlitchRow && rand.Float32() > 0.5 {
					sb.WriteRune(staticPool[rand.Intn(len(staticPool))])
				} else {
					sb.WriteByte(textStr[charIdx])
				}
				continue
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
