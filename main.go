package main

import (
	"fmt"

	"Terminal/scenes"
)

func main() {
	// Set Terminal Window Title
	fmt.Print("\033]0;TerminalLOOP\007")

	// Scene Management
	currentScene := "main_menu"

	for currentScene != "exit" && currentScene != "" {
		switch currentScene {
		case "main_menu":
			currentScene = scenes.RunMainMenu()
		case "proto":
			currentScene = scenes.RunProto()
		default:
			currentScene = "exit"
		}
	}
}
