# Student Records System

This repository contains:
- `main.cpp`: the C++ console program for the class requirement.
- `index.html`, `style.css`, `script.js`: a browser-based demonstration interface that can be published with GitHub Pages.

## Demo login
- Student: `STU001` / `1234`
- Office staff: `admin` / `admin123`

## Publish the website
1. Upload all files in this folder to the root of the GitHub repository.
2. In GitHub, open **Settings → Pages**.
3. Under Build and deployment, choose **Deploy from a branch**.
4. Select branch **main** and folder **/(root)**, then Save.
5. Wait for GitHub Pages to publish the site.

## Important project note
GitHub Pages serves static website files. It does not compile or run `main.cpp`. The browser interface is a classroom demonstration and stores demo requests in that browser's local storage. The C++ source is included separately for the C++ requirement; a real shared online system would need a separately hosted C++ backend and database. Do not use real student personal information or passwords in this demo.
