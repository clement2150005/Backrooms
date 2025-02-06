#!/bin/bash

mv minilibx-linux .minilibx-linux
norminette | grep -v OK! | grep -v "Comment is invalid in this scope" | grep -v "Empty line in function" | grep -v "line too long"
mv .minilibx-linux minilibx-linux
