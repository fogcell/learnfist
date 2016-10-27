set nocompatible              " 这是必需的 
    filetype off                  " 这是必需的 
    colorscheme molokai     
    let g:molokai_original = 1
    " 你在此设置运行时路径 
    set rtp+=~/.vim/bundle/Vundle.vim  
     
    " vundle初始化 
    call vundle#begin()  
     
    " 这应该始终是第一个 
        Plugin 'gmarik/Vundle.vim' 
    	Bundle 'bling/vim-airline'
    	Bundle 'Valloric/YouCompleteMe'
		"Bundle 'vim-airline/vim-airline-themes'
		Bundle  'Lokaltog/vim-powerline'
		let g:Powerline_symbols='unicode'
		Bundle  'ctrlpvim/ctrlp.vim'
		"YouCompleteMe 
		nnoremap <leader>gl :YcmCompleter GoToDeclaration<CR>
		nnoremap <leader>gf :YcmCompleter GoToDefinition<CR>
		nnoremap <leader>gg :YcmCompleter GoToDefinitionElseDeclaration<CR>
		let g:ycm_global_ycm_extra_conf='~/.vim/bundle/YouCompleteMe/cpp/ycm/.ycm_extra_conf.py'
		" NerdTree use <F2>
		Bundle 'scrooloose/nerdtree'
		let NERDTreeWinPos='left'
		let NERDTreeWinSize=31
		let NERDTreeChDirMode=1
		map <F2> :NERDTreeToggle<CR>
		autocmd bufenter * if (winnr("$") == 1 && exists("b:NERDTreeType")&& b:NERDTreeType == "primary") | q | endif
		"--ctags setting--
		"
		"" 按下F5重新生成tag文件，并更新taglist

		map <F5> :!ctags -R --c++-kinds=+p --fields=+iaS --extra=+q .<CR><CR> :TlistUpdate<CR>

		imap <F5> <ESC>:!ctags -R --c++-kinds=+p --fields=+iaS --extra=+q .<CR><CR> :TlistUpdate<CR>

		set tags=tags

		set tags+=./tags "add current directory's generated tags file
		" Taglist  use <F3>
		Bundle 'taglist.vim'
		let Tlist_Auto_Update=1
	   	let Tlist_Auto_Open = 0
		let Tlist_Use_Right_Window=1  
		let Tlist_Show_One_File=0  
		let Tlist_File_Fold_Auto_Close=0  
		let Tlist_Exit_OnlyWindow=1
		map <F3> :TlistToggle<CR>
    		call vundle#end()            " required 
		"end 
		set number " Enable line number "显示行号
		set laststatus=2
		set tabstop=4            "设置Tab键的宽度，可以更改，如：宽度为2
		set shiftwidth=4    "      (表示每一级缩进的长度)
		set softtabstop=4   "   （表示在编辑模式的时候按退格键的时候退回缩进的长度）
		syntax on  "gaoliang
		set autoindent  
    	filetype plugin indent on   " required
