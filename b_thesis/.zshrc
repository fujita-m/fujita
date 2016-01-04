export LANG=ja_JP.UTF-8
#history
HISTFILE=$HOME/.zsh-history
#メモリに保存する履歴の数
HISTSIZE=100000
#保存する履歴の数
SAVEHIST=100000
#コアダンプのサイズを制限
limit coredumpsize 102400
#出力の末尾に改行コードが無い
unsetopt promptcr
#Use color
setopt prompt_subst
#Don't use beep
setopt nobeep
#jobs long
setopt long_list_jobs
#show file type
setopt list_types
#Auto resume
setopt auto_resume
#auto list
setopt auto_list
setopt hist_ignore_dups
#auto add cd history
setopt auto_pushd
#dont add history if same directory
setopt pushd_ignore_dups
#automenu
setopt auto_menu
#add start time and end time to history file
setopt extended_history
#コマンドの引数を補完する
autoload -U compinit
compinit
#プロンプトの設定
PROMPT="%n@%m: "
PROMPT2="%_%% "
SPROMPT="%r is correct? [n,y,a,e]: "
setopt magic_equal_subst
setopt hist_verify
setopt numeric_glob_sort
setopt print_eight_bit
setopt share_history
setopt correct
setopt brace_ccl
#ls color
alias ls='ls --color=auto'
#compctl
compctl -f vim
compctl -/ cd
compctl -F man
