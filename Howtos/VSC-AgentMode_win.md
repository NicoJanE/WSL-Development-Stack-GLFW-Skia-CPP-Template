---
layout: default_c

RefPages:
- setup_linux
- setup_win
- building_project
--- 

# GLFW-Skia C++ Template <span style="color: #409EFF; font-size: 0.6em; font-style: italic;"> -  What VSC Agent(Windows)</span>

This will try to automatically (or semi-automatically) set up the Windows environment for our project. It uses the Visual Studio Code **Copilot Agent**.

I'm not sure how reliable this is. It worked for me after a lot of tweaking and adjusting the documentation (and perhaps a few unfriendly words directed at Copilot 😉). I tried disabling the "Continue?" prompt, but it still keeps asking,  I haven't found a fix for that yet.

<details class="nje-remark-box">
<summary>Feedback & Things that can go wrong
</summary>
I'm curious how this works for others. Please let me know in the discussion section. I will set up an issue titled **"VSC Agent Mode Experience"** you can add your experience there if you like. Based on my experience, here are a few things that might go wrong:</small>
  
**What can go wrong**

- GLFW 3.4 is downloaded to the wrong folder, causing the process to stop.  
  👉 **Fix:** Move the files to the expected location.
- Copilot may skip updating the Makefiles.  
  👉 **Fix:** At the end, ask Copilot:  
  *"Something tells me you forgot to update the Makefiles — did you?"*
- it removed the **opengl32** library  from the ***window.cmake*** file(GLFW_LIBS_WIN_LOCAL) which resulted in errors while running <span class="nje-cmd-inline-sm">./build.ps1</span>
- ✅ **Always ask at the end:** *"Did you skip a step?"* after Copilot finishes.

</details>

<span class="nje-br3"> </span>

## Prepare for Installation With VSC Agent

1. Open **Visual Studio Code**.
2. Open **Copilot** and ensure **Agent** is selected from the dropdown.
3. Recommended model: **GPT-4.1**.
4. Make sure your terminal is at the project root.
5. Enter the question(s) for steps one and two.

<span class="nje-br1"> </span>

## Steps for Windows

### Step 1 Create open new project.

Enter the following text, and follow the instructions in Copilot:
> <small>Note This is the same step as in the procedure as in the Linux based Copilot instructions [here](VSC-AgentMode_lin) in that case **skip this step** </small>

<pre class="nje-cmd-multi-line-sm">
Clone the GitHub repository https://github.com/NicoJanE/WSL-Development-Stack-GLFW-Skia-CPP-Template into a new subfolder named MyApp inside d:\Temp, and open that folder as a project in Visual Studio Code.
</pre>

<span class="nje-br1"> </span>

## Step 2 Build Windows environment

Assuming the *Step 1* was successful created and the project folder is  opened it in VSC.
Enter the following instruction into you PowerShell :

<pre class="nje-cmd-multi-line-sm">
Automate all steps from the referenced setup guide #fetch https://nicojane.github.io/WSL-Development-Stack-GLFW-Skia-CPP-Template/Howtos/setup_win, strictly in the order written. For each step:

- First tel me which steps your going to do and number them
- Stick to the order/sequence as defined!
- Use the command as defined in this document, do't change them!
- Do not perform any action before its place in the document; treat each bullet or numbered step as a mandatory checkpoint.
- Only create folders, download, unzip, move, or build when explicitly instructed.
- Always follow the literal wording and order; if ambiguous, default to the document’s sequence.
- Do not fix or change folder structure; report and stop on errors.
- Automate each step and proceed immediately to the next.
- If multiple options exist, choose the one marked 'Preferred'.
- When using msbuild.exe, first search for its location, then run vcvars64.bat (default path provided) before executing the build command.
- Do not pause or request any user confirmation between steps; proceed automatically to the next step as soon as the previous one completes successfully
</pre>

<span class="nje-br1"> </span>

## Step 3 Check!

**Always ask at the end: 'Did you skip a step ?' after Copilot is finished**

<span style="color: #6d757dff; font-size: 13px; font-style: italic;"> <br>
<i><b>License</b><br>This file is part of: **GLFW-Skia C++ Template Stack**  Copyright (c) 2025-2026 Nico Jan Eelhart.This repository is [MIT licensed](../MIT-license.md) and free to use. For optional commercial support, customization, training, or long-term maintenance, see [COMMERCIAL.md](../COMMERCIAL.md).</i>
</span>

<p align="center">─── ✦ ───</p>
