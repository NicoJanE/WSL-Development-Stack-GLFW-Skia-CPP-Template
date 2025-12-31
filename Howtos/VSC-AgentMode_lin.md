---
layout: default_c

RefPages:
- setup_linux
- setup_win
- building_project
--- 

# GLFW-Skia C++ Template <span style="color: #409EFF; font-size: 0.6em; font-style: italic;"> -  What VSC Agent(Linux)</span>
![MIT License](https://img.shields.io/badge/License-MIT-green) ![Commercial Services Available](https://img.shields.io/badge/Services-Optional-blue)

## Introduction

This will try to automatically (or semi-automatically) set up the Linux WSL environment for our project. It uses the Visual Studio Code **Copilot Agent**.
This may not be 100% reliable and  need more checking probably.

>**Feedback**  
<small>
I'm curious how this works for others. Please let me know in the discussion section. I will set up an issue titled **"VSC Agent Mode Experience"** you can add your experience there if you like.
</small>

<div class="nje-br1"> </div>

## Prepare for Installation With VSC Agent

1. Open Visual studio
1. open 'Copilot' and make sure you have chosen 'Agent' in the drop down
1. Best use: GPT-4.1
1. Make sure your VSC Terminal is in the project root
1. Enter the question of step one and two.

<div class="nje-br1"> </div>

## Steps for Linux WSL

### Step 1 Create open new project

Enter the following text, and follow the instructions in Copilot:
> <small>Note This is the same step as in the procedure as in the Windows based Copilot instructions [here](VSC-AgentMode_win) in that case **skip this step** </small>

<pre class="nje-cmd-multi-line-sm">Clone the GitHub repository https://github.com/NicoJanE/WSL-Development-Stack-GLFW-Skia-CPP-Template into a new subfolder named MyApp inside d:\Temp, and open that folder as a project in Visual Studio Code.
  </pre>

<div class="nje-br1"> </div>

## Step 2 Build Linux(WSL) environment
Enter the variables below and after that enter this text in Copilot 

<pre class="nje-cmd-multi-line-sm">
Automate all steps from the referenced setup guide #fetch https://nicojane.github.io/WSL-Development-Stack-GLFW-Skia-CPP-Template/Howtos/setup_linux.agent.md, strictly in the order written.
Aks the user to combine all suitable WSL steps into one or two scrip, or to execute them separately, but in both cases you should run the script(s). Take the following variable into account variables are all uppercase and for a space a _ (underscore) is used :
- A variable that holds the project root of the project:
  - PROJECT_ROOT: `D:\Temp\MyApp3`
- A variable that points to an exported WSL file which we will import via the setup guide:
  - WSL_EXPORT_FILE: `D:\WSL\WSL-Exports\Debian-clean.tar`
- A variable that points to the location of the WSL destination location:
  -WSL_DEST_LOC: `D:\Temp\MyApp3\_WSLData`
- A variable that points to the name of the WSL destination (the one we going to create) note that the Name of the WSL Destination will be a folder in this location :
  -WSL_DEST_NAME: test3 

Also take these rules into account!: 
- The commands are executed in the WSL from Windows
- The script should run all steps from the referenced setup guide, including any manual edits (like updating CMake/make files) and verification steps.
- That after running the script, you expect a summary of what was executed and confirmation that each step (including file edits) was completed.
- That you want explicit confirmation if any step was skipped or not possible to automate.
- Always report any errors encountered during the build process.
</pre>

**Note**
This step may ask you if it should combine all WSL instructions into one or not, you can answer this one of the two ways:
 - *'Yes combine and continue`*  -> Less user interaction, but also less clear what is executed 
 - *'No Separated steps please, continue'* -> This will guide you step by step through the procedure, more interaction

<div class="nje-br1"> </div>

## Step 3 Check

**Always** ask at the end: 'Did you skip a step ?' after Copilot is finished

<span style="color: #6d757dff; font-size: 13px; font-style: italic;"> <br>
<i><b>License</b><br>This file is part of: **GLFW-Skia C++ Template Stack**  Copyright (c) 2025-2026 Nico Jan Eelhart.This repository is [MIT licensed](MIT-license.md) and free to use. For optional commercial support, customization, training, or long-term maintenance, see [COMMERCIAL.md](COMMERCIAL.md).</i>
</span>

<br>
<br>
<p align="center">─── ✦ ───</p>
