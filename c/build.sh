#!/bin/bash

# Color codes
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Icons
CHECK="✅"
CROSS="❌"
ROCKET="🚀"
HAMMER="🔨"
SPARKLES="✨"

# Functions for additional commands
format() {
    echo -e "${BLUE}${SPARKLES} Formatting code...${NC}"
    # Only format files that actually exist
    find src/ -name "*.c" -o -name "*.h" | xargs -r clang-format -i
    echo -e "${GREEN}${CHECK} Formatting complete${NC}"
}

display() {
    # Clear screen at the start for clean interface
    clear

    echo -e "${BLUE}${SPARKLES} Available executables:${NC}"

    # Check if build/bin exists
    if [ ! -d "build/bin" ]; then
        echo -e "${RED}${CROSS} build/bin directory not found${NC}"
        return 1
    fi

    # Get all executables
    all_executables=()
    while IFS= read -r -d '' file; do
        all_executables+=("$file")
    done < <(find build/bin -maxdepth 1 -type f -executable -print0 2>/dev/null)

    if [ ${#all_executables[@]} -eq 0 ]; then
        echo -e "${YELLOW}No executable files found in build/bin${NC}"
        return
    fi

    # Show total count
    echo -e "${BLUE}Found ${#all_executables[@]} executable(s) in build/bin${NC}"
    echo

    # Ask for search term
    echo -e "${YELLOW}Search options:${NC}"
    echo -e "  ${BLUE}[Enter search term]${NC} Search for specific files"
    echo -e "  ${BLUE}[*]${NC} Show all files"
    echo -e "  ${BLUE}[q]${NC} Quit"
    echo
    read -p "Search (partial name or * for all): " search_term

    # Handle quit
    if [[ "$search_term" == "q" || "$search_term" == "Q" ]]; then
        clear
        echo -e "${BLUE}Cancelled${NC}"
        return
    fi

    # Filter executables based on search
    filtered_executables=()
    if [[ "$search_term" == "*" || -z "$search_term" ]]; then
        # Show all
        filtered_executables=("${all_executables[@]}")
    else
        # Search for matching files (case-insensitive)
        for exe in "${all_executables[@]}"; do
            filename=$(basename "$exe")
            # Case-insensitive partial match
            if [[ "${filename,,}" == *"${search_term,,}"* ]]; then
                filtered_executables+=("$exe")
            fi
        done
    fi

    # Check if any matches found
    if [ ${#filtered_executables[@]} -eq 0 ]; then
        clear
        echo -e "${RED}${CROSS} No executables found matching '$search_term'${NC}"
        echo -e "${YELLOW}Available files:${NC}"
        for exe in "${all_executables[@]}"; do
            echo -e "  ${GREEN}$(basename "$exe")${NC}"
        done
        echo
        echo -e "${BLUE}Press Enter to search again...${NC}"
        read
        display # Restart search
        return
    fi

    # Clear screen before showing results
    clear

    # Display filtered results header
    echo -e "${BLUE}${SPARKLES} Executable Search Results${NC}"
    echo
    if [[ "$search_term" == "*" || -z "$search_term" ]]; then
        echo -e "${GREEN}${CHECK} Showing all ${#filtered_executables[@]} executable(s):${NC}"
    else
        echo -e "${GREEN}${CHECK} Found ${#filtered_executables[@]} executable(s) matching '$search_term':${NC}"
    fi
    echo

    # Display numbered list
    for i in "${!filtered_executables[@]}"; do
        filename=$(basename "${filtered_executables[$i]}")
        # Highlight search term if not showing all
        if [[ "$search_term" != "*" && -n "$search_term" ]]; then
            # Simple highlight
            highlighted_name=$(echo "$filename" | sed "s/${search_term}/${search_term}/gi")
            echo -e "${GREEN}$((i + 1)). $highlighted_name${NC} ${BLUE}(./${filtered_executables[$i]})${NC}"
        else
            echo -e "${GREEN}$((i + 1)). $filename${NC} ${BLUE}(./${filtered_executables[$i]})${NC}"
        fi
    done

    echo
    echo -e "${BLUE}Options:${NC}"
    echo -e "  ${YELLOW}[1-${#filtered_executables[@]}]${NC} Run selected executable"
    echo -e "  ${YELLOW}[a]${NC} Run all filtered executables"
    echo -e "  ${YELLOW}[s]${NC} Search again"
    echo -e "  ${YELLOW}[Enter]${NC} Just list (no execution)"
    echo
    read -p "Your choice: " choice

    case "$choice" in
    [1-9] | [1-9][0-9])
        if [ "$choice" -ge 1 ] && [ "$choice" -le ${#filtered_executables[@]} ]; then
            selected_file="${filtered_executables[$((choice - 1))]}"

            # Clear screen before execution
            clear
            echo -e "${ROCKET} Running: $(basename "$selected_file")${NC}"
            echo "========================================"
            "$selected_file"
            echo "========================================"
            echo -e "${GREEN}${CHECK} Execution completed${NC}"
            echo
            echo -e "${BLUE}Press Enter to continue...${NC}"
            read

            # Ask if user wants to run another or exit
            clear
            echo -e "${YELLOW}What would you like to do next?${NC}"
            echo -e "  ${GREEN}[1]${NC} Search/run another executable"
            echo -e "  ${GREEN}[2]${NC} Exit to shell"
            echo
            read -p "Your choice (1/2): " next_choice

            case "$next_choice" in
            1)
                display # Restart display function
                ;;
            *)
                clear
                echo -e "${GREEN}${CHECK} Done!${NC}"
                ;;
            esac
        else
            echo -e "${RED}${CROSS} Invalid selection (1-${#filtered_executables[@]})${NC}"
            echo -e "${BLUE}Press Enter to try again...${NC}"
            read
            display # Restart on invalid selection
        fi
        ;;
    [aA])
        # Clear screen before running all
        clear
        echo -e "${ROCKET} Running all filtered executables...${NC}"
        echo

        for exe in "${filtered_executables[@]}"; do
            echo -e "${BLUE}🔹 Running: $(basename "$exe")${NC}"
            echo "----------------------------------------"
            "$exe"
            echo "----------------------------------------"
            echo
        done

        echo -e "${GREEN}${CHECK} All executions completed${NC}"
        echo
        echo -e "${BLUE}Press Enter to continue...${NC}"
        read

        # Ask what to do next
        clear
        echo -e "${YELLOW}What would you like to do next?${NC}"
        echo -e "  ${GREEN}[1]${NC} Search/run more executables"
        echo -e "  ${GREEN}[2]${NC} Exit to shell"
        echo
        read -p "Your choice (1/2): " next_choice

        case "$next_choice" in
        1)
            display
            ;;
        *)
            clear
            echo -e "${GREEN}${CHECK} Done!${NC}"
            ;;
        esac
        ;;
    [sS])
        # Clear and restart search
        display
        ;;
    "")
        clear
        echo -e "${BLUE}Listed filtered executables only${NC}"
        echo -e "${BLUE}Press Enter to search again or Ctrl+C to exit...${NC}"
        read
        display
        ;;
    *)
        echo -e "${RED}${CROSS} Invalid option${NC}"
        echo -e "${BLUE}Press Enter to try again...${NC}"
        read
        display # Restart on invalid option
        ;;
    esac
}

clean() {
    echo -e "${YELLOW}${HAMMER} Cleaning build directory...${NC}"
    rm -rf build/
    echo -e "${GREEN}${CHECK} Clean complete${NC}"
}

# Handle arguments
if [ "$1" = "format" ]; then
    format
    exit 0
elif [ "$1" = "display" ]; then
    display
    exit 0
elif [ "$1" = "clean" ]; then
    clean
    exit 0
fi

# Default build process
echo -e "${BLUE}${ROCKET} Start the building process...${NC}"

if cmake -B build; then
    echo -e "${GREEN}${CHECK} CMake configuration successful${NC}"
else
    echo -e "${RED}${CROSS} CMake configuration failed${NC}"
    exit 1
fi

if cmake --build build; then
    echo -e "${GREEN}${CHECK} Build successful! Run with: ${YELLOW}./build/bin/${NC}"
else
    echo -e "${RED}${CROSS} Build failed${NC}"
    exit 1
fi
