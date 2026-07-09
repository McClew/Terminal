package main

import (
	"fmt"

	"Terminal/scenes"
	"Terminal/terminal"
)

func main() {
	// Set Terminal Window Title
	fmt.Print("\033]0;TerminalLOOP\007")

	term, rootContainer := terminal.StartTerminal()
	defer term.Close()

	// Scene Management
	currentScene := "main_menu"

	for currentScene != "exit" && currentScene != "" {
		switch currentScene {
		case "main_menu":
			currentScene = scenes.RunMainMenu(term, rootContainer)
		case "proto":
			currentScene = scenes.RunProto(term, rootContainer)
		default:
			currentScene = "exit"
		}
	}
}
