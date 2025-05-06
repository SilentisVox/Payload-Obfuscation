function Build
{
    write-host "**** Silentis Vox Malware Environment ****"
    write-host "silentis v.1.0.0 (64 bit) `n"

    $start_time                         = get-date

    write-host "Build Started at: $(get-date -format 'hh:mm:ss tt') `n"

    $tcc                                = "./Compiler/tcc/tcc.exe"
    $nasm                               = "./Compiler/nasm/nasm.exe"

    $script:RESULT                      = $TRUE

    ## -------------------------------- #### -------------------------------- #### -------------------------------- ##

    if (-not (test-path $tcc))
    {
        write-host "[!] Failed To Locate $tcc" -foregroundcolor red
        return
    }

    if (-not (test-path $nasm))
    {
        write-host "[!] Failed To Locate $nasm" -foregroundcolor red
        return
    }

    ## -------------------------------- #### -------------------------------- #### -------------------------------- ##

    function ASM ($ASMFILE)
    {
        & $nasm -f elf64 -o "$($ASMFILE.directoryname)\$($ASMFILE.basename).obj" $ASMFILE.fullname > $NULL 2>&1
    }

    function TTCC ($name, $SOURCEDIRECTORY, $SOURCEFILES)
    {
        & $tcc -o "$SOURCEDIRECTORY\$name.exe" $SOURCEFILES > $NULL 2>&1
    }

    ## -------------------------------- #### -------------------------------- #### -------------------------------- ##

    function SUBPROJECT ($name)
    {
        write-host "     ╰─ $name"

        $ASMFILES                       = get-childitem $name.fullname -filter "*.asm"

        if ($ASMFILES)
        {
            foreach ($ASMFILE in $ASMFILES)
            {
                ASM $ASMFILE
            }
        }

        $SOURCEDIRECTORY                = $name.fullname
        $SOURCEFILES                    = get-childitem $name.fullname | where-object { $_.extension -in @(".c", ".obj") } | % { $_.fullname }

        TTCC $name $SOURCEDIRECTORY $SOURCEFILES

    }

    function PROJECT ($name)
    {
        write-host "Building" -foregroundcolor green
        write-host "  $name"

        $SUBPROJECTS                   = get-childitem $name
        
        foreach ($SUBPROJECT in $SUBPROJECTS)
        {
            SUBPROJECT $SUBPROJECT
        }
    }

    ## -------------------------------- #### -------------------------------- #### -------------------------------- ##

    function INDIVIDUAL ($name)
    {
        write-host "     ╰─ $name"

        $OBJECTFILES                    = get-childitem $name.fullname -filter "*.obj" | % { $_.fullname }

        if ($OBJECTFILES)
        {
            foreach ($FILE in $OBJECTFILES)
            {
                remove-item $FILE
            }
        }

        $EXE                            = get-childitem $name.fullname -filter "*.exe"

        if (-not $EXE)
        {
            write-host "Error" -foregroundcolor red -nonewline; write-host ": Failed To Build '$SUBPROJECT.exe'"
            $script:RESULT              = $FALSE
        }
    }

    function CHECK ($name)
    {
        write-host "Checking" -foregroundcolor yellow
        write-host "  $name"

        $SUBPROJECTS                   = get-childitem $name
        
        foreach ($SUBPROJECT in $SUBPROJECTS)
        {
            INDIVIDUAL $SUBPROJECT
        }
    }

    $PROJECTS                           = @("AES Encryption", "MAC Obfuscation")

    ## -------------------------------- #### -------------------------------- #### -------------------------------- ##

    foreach ($PROJECT in $PROJECTS)
    {
        PROJECT $PROJECT
    }

    foreach ($PROJECT in $PROJECTS)
    {
        CHECK $PROJECT
    }

    if ($RESULT)
    {
        write-host "Build Successful!" -foregroundcolor blue
    }
    else 
    {
        write-host "Warning" -foregroundcolor magenta -nonewline; write-host ": Build Failed. Waiting On Jobs To Finish . . ."
    }

    write-host "`nBuild Finished at: $(get-date -format 'hh:mm:ss tt') `n"

    $end_time                           = get-date
    $duration                           = $end_time - $start_time

    write-host "Elapsed Time: $duration"
}

Build
