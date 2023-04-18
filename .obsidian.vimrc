
" While searching though a file incrementally highlight matching characters as you type.
set incsearch
" Highlight cursor line underneath the cursor horizontally.
set cursorline
" Highlight cursor line underneath the cursor vertically.
set cursorcolumn
" Use highlighting when doing a search.
set hlsearch
" Ignore capital letters during search.
set ignorecase
" Show the mode you are on the last line.
set showmode.

"Move visual line :
nmap j gj
nmap k gk
nmap 0 g0
nmap $ g$
nmap [[ :pHead
nmap ]] :nHead
"
"
vmap j gj
vmap k gk

"CTRl+C, 
unmap <C-c> 
" Yank to system clipboard
set clipboard=unnamed

" Emulate Folding https://vimhelp.org/fold.txt.html#fold-commands
exmap togglefold obcommand editor:toggle-fold
nmap zo :togglefold
nmap zc :togglefold
nmap za :togglefold

exmap unfoldall obcommand editor:unfold-all
nmap zR :unfoldall

exmap foldall obcommand editor:fold-all
nmap zM :foldall
5
" Emulate Tab Switching https://vimhelp.org/tabpage.txt.html#gt
" requires Cycle Through Panes Plugins https://obsidian.md/plugins?id=cycle-through-panes
exmap tabnext obcommand cycle-through-panes:cycle-through-panes
nmap gt :tabnext
exmap tabprev obcommand cycle-through-panes:cycle-through-panes-reverse
nmap gT :tabprev.