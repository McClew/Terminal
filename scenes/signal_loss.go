package scenes

import (
	"fmt"
	"math/rand"
	"strings"
	"time"

	tea "github.com/charmbracelet/bubbletea"
)

// Define our states
type gameState int

const (
	stateIntro gameState = iota
	statePlaying
)

// Core messages for our game loop
type tickMsg time.Time
type endIntroMsg struct{}

type model struct {
	state        gameState
	frame        int
	windowWidth  int
	windowHeight int
}

func initialModel() model {
	return model{
		state: stateIntro,
		frame: 0,
	}
}

// Commands to handle timings
func nextFrameCmd() tea.Cmd {
	return tea.Tick(time.Millisecond*50, func(t time.Time) tea.Msg {
		return tickMsg(t)
	})
}

func endIntroCmd() tea.Cmd {
	return func() tea.Msg {
		time.Sleep(3 * time.Second) // Display the glitch for 3 seconds
		return endIntroMsg{}
	}
}

func (m model) Init() tea.Cmd {
	// Start both the animation tick stream AND the 3-second scene timer
	return tea.Batch(nextFrameCmd(), endIntroCmd())
}

func (m model) Update(msg tea.Msg) (tea.Model, tea.Cmd) {
	switch msg := msg.(type) {

	case tea.WindowSizeMsg:
		m.windowWidth = msg.Width
		m.windowHeight = msg.Height
		return m, nil

	case tickMsg:
		if m.state == stateIntro {
			m.frame++
			return m, nextFrameCmd() // Loop the animation tick
		}

	case endIntroMsg:
		m.state = statePlaying
		return m, tea.Quit
	}

	return m, nil
}

func (m model) View() string {
	switch m.state {
	case stateIntro:
		return m.renderGlitch()
	case statePlaying:
		return ""
	default:
		return ""
	}
}

// Generates a flickering, offset static effect dynamically
func (m model) renderGlitch() string {
	var sb strings.Builder

	// The characters used to simulate heavy "white noise" and hardware static
	staticPool := []rune{'░', '▒', '▓', '█', ' ', '▖', '▗', '▘', '▙', '▚', '▛', '▜'}

	// Create a responsive grid layout based on terminal size
	height := m.windowHeight
	if height == 0 {
		height = 20
	}
	width := m.windowWidth
	if width == 0 {
		width = 60
	}

	midY := height / 2

	for y := 0; y < height; y++ {
		// Introduce structural horizontal glitches on specific frames
		isGlitchRow := (y+m.frame)%7 == 0 && rand.Float32() > 0.4

		for x := 0; x < width; x++ {
			// Center the text "SIGNAL LOSS" but make it snap/glitch horizontally
			if y == midY && x > (width/2)-10 && x < (width/2)+10 {
				text := "  NO SIGNAL  "
				charIdx := x - ((width / 2) - 10)

				if charIdx < len(text) {
					if isGlitchRow && rand.Float32() > 0.5 {
						// Glitch out the text into pure static
						sb.WriteRune(staticPool[rand.Intn(len(staticPool))])
					} else {
						sb.WriteByte(text[charIdx])
					}
					continue
				}
			}

			// Generate the background static noise
			if isGlitchRow {
				// Tear the screen sideways by printing solid blocks
				sb.WriteRune('█')
			} else {
				// Mix text density dynamically over time
				idx := (rand.Intn(len(staticPool)) + m.frame) % len(staticPool)
				sb.WriteRune(staticPool[idx])
			}
		}
		sb.WriteString("\n")
	}

	return sb.String()
}

func RenderSignalLossScene() {
	p := tea.NewProgram(initialModel())
	if _, err := p.Run(); err != nil {
		fmt.Printf("Error running game: %v", err)
	}
}
