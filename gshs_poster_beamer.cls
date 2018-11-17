%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% GSHS POSTER cls file
%%% for 기초R&E conference
%%% Chinook Mok
%%% 2018.10.31
%%% Final Report <-> Conference Poster
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\ProvidesClass{gshs_poster_beamer}
\LoadClass{beamer}
\usetheme{Berkeley}

\usepackage[orientation=portrait,size=a1,scale=1.4]{beamerposter}



\usepackage{geometry}
\geometry{
  total={594mm, 841mm},
  left=20mm,
  right=20mm,
  top=5mm,
  bottom=5mm
}


%% 기본 패키지들
\usepackage{graphicx}
\usepackage{amsmath,amssymb}
\usepackage{xcolor}
\usepackage{tikz}
\usepackage{pgfplots}
\usepackage{kotex}



%% Define Colors
\definecolor{gshsblue}{RGB}{56,93,138}

%% Header Setup
\def\ptitle#1{\gdef\@ptitle{#1}}
\def\authorone#1{\gdef\@authorone{#1}}
\def\authortwo#1{\gdef\@authortwo{#1}}
\def\authorthree#1{\gdef\@authorthree{#1}}
\def\teacher#1{\gdef\@teacher{#1}}


%% Header
\renewcommand{\maketitle}{
  \begin{center}
  \begin{tikzpicture}
    \draw[gshsblue,line width=2pt,rounded corners=1cm] (-0.5\textwidth,-4.85) -- (0.5\textwidth,-4.85) -- (0.5\textwidth,4.85) -- (-0.5\textwidth,4.85) -- cycle;
    \node[right] at (-0.5\textwidth,0) {\includegraphics[width=8cm]{./logo/gshs_logo(new)(pdf).pdf}};
    \node[left] at (0.5\textwidth,0) {\includegraphics[width=8cm]{./logo/gshslogo2(jpg).jpg}};
    \node[below=0.6cm,text width=36cm,align=center] at (0,4.8) {\huge\bfseries\sffamily\@ptitle};
    \node[anchor=south west] at (4,-2.1) {\bfseries\sffamily 경기과학고등학교 1학년};
    \node[anchor=south west] at (4,-3.4) {\bfseries\sffamily 연\hspace{0.67em}구\hspace{0.67em}자: {\@authorone}, {\@authortwo} {\@authorthree}};
    \node[anchor=south west] at (4,-4.7) {\bfseries\sffamily 지도\hspace{0.5em}교사: \@teacher};
  \end{tikzpicture}
  \end{center}
}

%% Footer Setting
\usepackage{fancyhdr}
\renewcommand{\headrulewidth}{0.0pt}
\renewcommand{\footrulewidth}{0.0pt}
%\fancyhead{}
\fancyfoot{
  \begin{tikzpicture}[overlay,remember picture]
    \node (footer) at ([yshift=0.5cm]current page.south east) [anchor=south east]{\includegraphics[width=19.8cm,trim={8.5cm 13.3cm 2.1cm 4.8cm},clip]{./logo/gshs_logo_full(new).pdf}};
  \end{tikzpicture}
}

%%% figure & table setup
%\graphicspath{{figures/}} 
\usepackage[font=small,labelfont=bf]{caption}
\captionsetup{labelsep=space}

%%%%%
%%%% Reference Setting %%%%
\bibliographystyle{gshs_poster_beamer}

\renewcommand\refname{REFERENCES}
%%%%%


\makeatletter
\let\@@magyar@captionfix\relax
\makeatother


%% Block Setting (framed block)
\usepackage[most]{tcolorbox}

\newtcolorbox{posterbox}[2][]{%
    colback=bg, 
    colframe=black,
    fonttitle=\bfseries\large,
    coltitle=black, 
    colbacktitle=bg,
    enhanced,
    attach boxed title to top left={yshift=-1.2mm, xshift=2mm},
  title=#2,
  #1}
  
