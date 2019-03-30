set nocompatible
filetype off
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()


"Plugin from Github
Plugin 'VundleVim/Vundle.vim'

Plugin 'vim-airline/vim-airline'
set t_Co=256
set laststatus=2
let g:airline#extensions#tabline#enabled = 1
let g:airline#extensions#tabline#left_sep = ' '
let g:airline#extensions#tabline#left_alt_sep = ' '
let g:airline#extensions#tabline#buffer_nr_show = 1
nnoremap [b :bp<CR>
nnoremap ]b :bn<CR>
map <leader>1 :b 1<CR>
map <leader>2 :b 2<CR>
map <leader>3 :b 3<CR>
map <leader>4 :b 4<CR>
map <leader>5 :b 5<CR>
map <leader>6 :b 6<CR>
map <leader>7 :b 7<CR>
map <leader>8 :b 8<CR>
map <leader>9 :b 9<CR>
"plugin from vimscript
Plugin 'The-NERD-tree'
"F2快捷键显示当前目录树
map <F2> :NERDTreeToggle<CR>
let NERDTreeWinSize=25

Plugin 'indentLine.vim'
Plugin 'delimitMate.vim'

Plugin 'taglist.vim'
map <F3> :Tlist<CR>
let Tlist_Use_Right_Window=1
let Tlist_Show_One_File=1
let Tlist_Exit_OnlyWindow=1
let Tlist_WinWidt=25
let Tlist_Ctags_Cmd="/usr/bin/ctags"
"Plugin from git


call vundle#end()

set autoread
set completeopt=preview,menu
filetype plugin indent on
set clipboard=unnamed
set ruler
set cursorline
set magic
set syntax=on
set confirm
set autoindent
set cindent
set tabstop=4
set softtabstop=4
set shiftwidth=4
set noexpandtab
set smarttab
set number
set history=1000
set hlsearch
set incsearch
set enc=utf-8
set fencs=utf-8,ucs-bom,shift-jis,gbk,gb2312,cp936
set langmenu=zh_CN.UTF-8
set helplang=cn
set showmatch
set matchtime=1

