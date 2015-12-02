 else if (tokens.at(0) == "ACALL" || tokens.at(0) == "LCALL") {
        unsigned address = magic_process(tokens.at(1));
        bool is_lib = false;
        if(tokens.at(1) == "PRINTF" || tokens.at(1) == "PUTS")
        {
            address = 132912;
            is_lib = true;
        }
        else
        {
            address= 66752;
        }
        CallStatement* newCall = new CallStatement;
        ADDRESS nativeDest = address - delta;
        newCall->setDest(nativeDest);
        Proc* destProc;
        std::transform(tokens.at(1).begin(), tokens.at(1).end(),tokens.at(1).begin(), ::tolower);
        char *name =  new char[tokens.at(1).length() + 1];
        strcpy(name, tokens.at(1).c_str());
        namesList[address] = name;
        funcsType[address] = is_lib;
        destProc = prog->newProc(name, nativeDest, is_lib);
        newCall->setDestProc(destProc);
        result.rtl = new RTL(pc, stmts);
        result.rtl->appendStmt(newCall);
        result.type = SD;
    }
    else if (tokens.at(0) == "ADD" || tokens.at(0) == "ADDC" || tokens.at(0) == "SUBB") {
        unsigned op1 = magic_process(tokens.at(1));
        unsigned op2 = magic_process(tokens.at(2));
        std::stringstream sstm;
        sstm << tokens.at(0) << "_A_";
        std::string name;
        if(tokens.at(2) == "@R0")
        {
            sstm << "RI0";
            name = sstm.str();
            char *name_ =  new char[name.length() + 1];
            strcpy(name_, name.c_str());
            stmts = instantiate(pc,name_);
        }
        else
        if(tokens.at(2) == "@R1")
        {
            sstm << "RI1";
            name = sstm.str();
            char *name_ =  new char[name.length() + 1];
            strcpy(name_, name.c_str());
            stmts = instantiate(pc,name_);
        }
        else
        if(op2 < 8)
        {
            sstm << "R" << op2;
            name = sstm.str();
            char *name_ =  new char[name.length() + 1];
            strcpy(name_, name.c_str());
            stmts = instantiate(pc, name_);
        }
        else
        if(op2 >= 9 && op2 <= 16)
        {
            sstm << "DIR";
            name = sstm.str();
            char *name_ =  new char[name.length() + 1];
            strcpy(name_, name.c_str());
            stmts = instantiate(pc, name_, Location::regOf(op2));
        }
        else
        if(op2 >= 100)
        {   
            
            unsigned new_constant = op2-4294967296;
            sstm << "IMM";
            name = sstm.str();
            char *name_ =  new char[name.length() + 1];
            strcpy(name_, name.c_str());
            if(op2 < u_constant  )
            stmts = instantiate(pc, name_, new Const(op2-100));
            else
            stmts = instantiate(pc, name_, new Const(new_constant));
        }
    }
    else if (tokens.at(0) == "NOP" ) {
        result.type = NOP;
        stmts = instantiate(pc,  "NOP");
    }
    else if (tokens.at(0) == "LJMP" || tokens.at(0) == "AJMP" || tokens.at(0) == "SJMP") {
        unsigned address = magic_process(tokens.at(1));
        CaseStatement* jump = new CaseStatement;
        jump->setIsComputed();
        result.rtl = new RTL(pc, stmts);
        result.rtl->appendStmt(jump);
        result.type = DD;
        jump->setDest(address);
    }
    else if (tokens.at(0) == "JMP" || tokens.at(0) == "JMP") {
        stmts = instantiate(pc,  "JMP_AADDDPTR");
    }
    else if (tokens.at(0) == "RR" || tokens.at(0) == "RRC" || tokens.at(0) == "RLC") {
        unsigned op1 = magic_process(tokens.at(1));
        if(op1 == 8)
        {
            std::stringstream sstm;
            sstm << tokens.at(0) << "_A";
            std::string name;
            name = sstm.str();
            char *name_ =  new char[name.length() + 1];
            strcpy(name_, name.c_str());
            stmts = instantiate(pc,  name_);
        }
    }
    else if (tokens.at(0) == "DEC" || tokens.at(0) == "INC") {
        unsigned op1 = magic_process(tokens.at(1));
        std::stringstream sstm;
        sstm << tokens.at(0) << "_";
        std::string name;
        if(tokens.at(1) == "@R0")
        {
            sstm << "RI0";
            name = sstm.str();
            char *name_ =  new char[name.length() + 1];
            strcpy(name_, name.c_str());
            stmts = instantiate(pc,name_);
        }
        else
        if(tokens.at(1) == "@R1")
        {
            sstm << "RI1";
            name = sstm.str();
            char *name_ =  new char[name.length() + 1];
            strcpy(name_, name.c_str());
            stmts = instantiate(pc,name_);
        }
        else
        if(tokens.at(1) == "DPTR")
        {
            sstm << "DPTR";
            name = sstm.str();
            char *name_ =  new char[name.length() + 1];
            strcpy(name_, name.c_str());
            stmts = instantiate(pc, name_);
        }
        else
        if(op1 < 8)
        {
            sstm << "R" << op1;
            name = sstm.str();
            char *name_ =  new char[name.length() + 1];
            strcpy(name_, name.c_str());
            stmts = instantiate(pc, name_);
        }
        else
        if(op1 == 8)
        {
            sstm << "A";
            name = sstm.str();
            char *name_ =  new char[name.length() + 1];
            strcpy(name_, name.c_str());
            stmts = instantiate(pc, name_);
        }
        else
        if(op1 >= 100)
        {
            unsigned new_constant = op1-4294967296;
            sstm << "DIR";
            name = sstm.str();
            char *name_ =  new char[name.length() + 1];
            strcpy(name_, name.c_str());
            if(op1 < u_constant  )
            stmts = instantiate(pc, name_, new Const(op1-100));
            else
            stmts = instantiate(pc, name_, new Const(new_constant));
        }
    }
    else if (tokens.at(0) == "CMP"){
        unsigned op1 = magic_process(tokens.at(1));
        stmts = instantiate(pc, "JB_DIR_IMM", Location::regOf(op1), new Const(100));
    }
    else if (tokens.at(0) == "JNB" || tokens.at(0) == "JB" || tokens.at(0) == "JBC") {
        unsigned op1 = magic_process(tokens.at(1));
        unsigned op2 = magic_process(tokens.at(2));
        /*std::stringstream sstm;
        sstm << tokens.at(0) << "_DIR_IMM";
        std::string name;
        unsigned new_constant = op2-4294967296;
        name = sstm.str();
        char *name_ =  new char[name.length() + 1];
        strcpy(name_, name.c_str());
        if(op2 < u_constant  )
        stmts = instantiate(pc, name_, new Const(op1), new Const(op2-100));
        else
        stmts = instantiate(pc, name_,  new Const(op1),new Const(new_constant));*/
        result.rtl = new RTL(pc, stmts); 
        BranchStatement* jump = new BranchStatement; 
        result.rtl->appendStmt(jump); 
        result.numBytes = 4; 
        jump->setDest(op2-100);
        jump->setCondType(BRANCH_JE);
    }

    else if (tokens.at(0) == "LCALL" || tokens.at(0) == "LCALL") {
        unsigned address = magic_process(tokens.at(1));
        bool is_lib = false;
        if(tokens.at(1) == "PRINTF" || tokens.at(1) == "PUTS")
        {
            address = 132912;
            is_lib = true;
        }
        else
        {
            address= 66752;
        }
        CallStatement* newCall = new CallStatement;
        ADDRESS nativeDest = address - delta;
        newCall->setDest(nativeDest);
        Proc* destProc;
        std::transform(tokens.at(1).begin(), tokens.at(1).end(),tokens.at(1).begin(), ::tolower);
        char *name =  new char[tokens.at(1).length() + 1];
        strcpy(name, tokens.at(1).c_str());
        destProc = prog->newProc(name, nativeDest, is_lib);
        newCall->setDestProc(destProc);
        result.rtl = new RTL(pc, stmts);
        result.rtl->appendStmt(newCall);
        result.type = SD;
    }
    else if (tokens.at(0) == "JC") {
        unsigned op1 = magic_process(tokens.at(1));
        unsigned new_constant = op1-4294967296;
        if(op1 < u_constant  )
        stmts = instantiate(pc, "JC_IMM", new Const(op1-100));
        else
        stmts = instantiate(pc, "JC_IMM", new Const(new_constant));
    }
    else if (tokens.at(0) == "JNC") {
        unsigned op1 = magic_process(tokens.at(1));
        unsigned new_constant = op1-4294967296;
        if(op1 < u_constant  )
        stmts = instantiate(pc, "JC_IMM", new Const(op1-100));
        else
        stmts = instantiate(pc, "JC_IMM", new Const(new_constant));
    }
    else if (tokens.at(0) == "ORL" || tokens.at(0) == "ANL" || tokens.at(0) == "XRL") {
        unsigned op1 = magic_process(tokens.at(1));
        unsigned op2 = magic_process(tokens.at(2));
        std::stringstream sstm;
        sstm << tokens.at(0) << "_";
        std::string name;
        if(op1 == 10 )
        {
            sstm << "C_";
            name = sstm.str();
            char *name_ =  new char[name.length() + 1];
            strcpy(name_, name.c_str());
            stmts = instantiate(pc,name_, new Const(op2));
        }
        if(op1 == 8)
        {
            sstm << "A_";
            if(tokens.at(2) == "@R0")
            {
                sstm << "RI0";
                name = sstm.str();
                char *name_ =  new char[name.length() + 1];
                strcpy(name_, name.c_str());
                stmts = instantiate(pc,name_);
            }
            else
            if(tokens.at(2) == "@R1")
            {
                sstm << "RI1";
                name = sstm.str();
                char *name_ =  new char[name.length() + 1];
                strcpy(name_, name.c_str());
                stmts = instantiate(pc,name_);
            }
            else
            if(op2 < 8)
            {
                sstm << "R" << op2;
                name = sstm.str();
                char *name_ =  new char[name.length() + 1];
                strcpy(name_, name.c_str());
                stmts = instantiate(pc, name_);
            }
            else
            if(op2 >= 100)
            {
                unsigned new_constant = op2-4294967296;
                sstm << "IMM";
                name = sstm.str();
                char *name_ =  new char[name.length() + 1];
                strcpy(name_, name.c_str());
                if(op2 < u_constant  )
                stmts = instantiate(pc, name_, new Const(op2-100));
                else
                stmts = instantiate(pc, name_, new Const(new_constant));
            }
            else
            if(op2 >= 9 && op2 <= 16)
            {
                sstm << "DIR";
                name = sstm.str();
                char *name_ =  new char[name.length() + 1];
                strcpy(name_, name.c_str());
                stmts = instantiate(pc, name_, Location::regOf(op2));
            }
        }
        else
        if(op1 >= 9 && op1 <= 16 )
        {
            sstm << "DIR_";
            if(op2 == 8)
            {
                sstm << "A";
                char *name_ =  new char[name.length() + 1];
                strcpy(name_, name.c_str());
                stmts = instantiate(pc, name_, Location::regOf(op1));
            }
            else
            if(op2 >= 100)
            {
                unsigned new_constant = op2-4294967296;
                sstm << "IMM";
                name = sstm.str();
                char *name_ =  new char[name.length() + 1];
                strcpy(name_, name.c_str());
                if(op2 < u_constant  )
                stmts = instantiate(pc, name_,Location::regOf(op1), new Const(op2-100));
                else
                stmts = instantiate(pc, name_,Location::regOf(op1), new Const(new_constant));
            }
        }
    }
    else if (tokens.at(0) == "JZ" || tokens.at(0) == "JNZ") {
        unsigned address = magic_process(tokens.at(1));
        std::stringstream sstm;
        sstm << tokens.at(0) << "_IMM";
        std::string name;
        name = sstm.str();
        char *name_ =  new char[name.length() + 1];
        strcpy(name_, name.c_str());
        stmts = instantiate(pc,name_, new Const(address));
    }
    else if (tokens.at(0) == "DIV" || tokens.at(0) == "MUL") {
        unsigned op1 = magic_process(tokens.at(1));
        if(op1 == 12)
        {
            std::stringstream sstm;
            sstm << tokens.at(0) << "_AB";
            std::string name;
            name = sstm.str();
            char *name_ =  new char[name.length() + 1];
            strcpy(name_, name.c_str());
            stmts = instantiate(pc,name_);
        }
    }
    else if (tokens.at(0) == "CPL" || tokens.at(0) == "CPL") {
        unsigned op1 = magic_process(tokens.at(1));
        if(op1 == 8)
        {
            stmts = instantiate(pc,"CPL_A");
        }
        else
        if(op1 == 10)
        {
            stmts = instantiate(pc,"CPL_C");
        }
        else
        if(op1 >= 100)
        {
            unsigned new_constant = op1-4294967296;
            if(op1 < u_constant  )
            stmts = instantiate(pc, "CPL_DIR", new Const(op1-100));
            else
            stmts = instantiate(pc, "CPL_DIR", new Const(new_constant));
        }
    }
    else if (tokens.at(0) == "CJNE") {
        unsigned op1 = magic_process(tokens.at(1));
        unsigned op2 = magic_process(tokens.at(2));
        unsigned op3 = magic_process(tokens.at(3));
        if(tokens.at(0) == "@R0")
        {
            if(op2 >= 100 && op3 >= 100)
            {
                int operand2 = 0;
                int operand3 = 0;
                if(op2 < u_constant  )
                operand2 = op2 -100;
                else
                operand2 = op2 - 4294967296;
                if(op3 < u_constant  )
                operand3 = op3 -100;
                else
                operand3 = op3 - 4294967296;
                stmts = instantiate(pc, "CJNE_RI0_IMM_IMM", new Const(operand2), new Const(operand3));
            }
        }
        else
        if(tokens.at(0) == "@R1")
        {
            if(op2 >= 100 && op3 >= 100)
            {
                int operand2 = 0;
                int operand3 = 0;
                if(op2 < u_constant  )
                operand2 = op2 -100;
                else
                operand2 = op2 - 4294967296;
                if(op3 < u_constant  )
                operand3 = op3 -100;
                else
                operand3 = op3 - 4294967296;
                stmts = instantiate(pc, "CJNE_RI1_IMM_IMM", new Const(operand2), new Const(operand3));
            }
        }
        else
        if(op1 < 8)
        {
            std::stringstream sstm;
            sstm << "CJNE_R" << tokens.at(0) << "_IMM_IMM";
            std::string name;
            name = sstm.str();
            char *name_ =  new char[name.length() + 1];
            strcpy(name_, name.c_str());
            if(op2 >= 100 && op3 >= 100)
            {
                int operand2 = 0;
                int operand3 = 0;
                if(op2 < u_constant  )
                operand2 = op2 -100;
                else
                operand2 = op2 - 4294967296;
                if(op3 < u_constant  )
                operand3 = op3 -100;
                else
                operand3 = op3 - 4294967296;
                stmts = instantiate(pc,name_, new Const(operand2), new Const(operand3));
            }
        }
        else
        if(op1 == 8)
        {
            if(op2 >= 100 && op3 >= 100)
            {
                int operand2 = 0;
                int operand3 = 0;
                if(op2 < u_constant  )
                operand2 = op2 -100;
                else
                operand2 = op2 - 4294967296;
                if(op3 < u_constant  )
                operand3 = op3 -100;
                else
                operand3 = op3 - 4294967296;
                stmts = instantiate(pc, "CJNE_A_IMM_IMM", new Const(operand2), new Const(operand3));
            }
            else
            {
                int operand3 = 0;
                if(op3 < u_constant  )
                operand3 = op3 -100;
                else
                operand3 = op3 - 4294967296;
                stmts = instantiate(pc, "CJNE_A_DIR_IMM", Location::regOf(op2), new Const(operand3));
            }
        }
    }
    else if (tokens.at(0) == "PUSH" || tokens.at(0) == "POP") {
        unsigned op1 = magic_process(tokens.at(1));
        std::stringstream sstm;
        sstm << tokens.at(0) << "_DIR";
        std::string name;
        name = sstm.str();
        char *name_ =  new char[name.length() + 1];
        strcpy(name_, name.c_str());
        if(op1 < 8)
        {
            stmts = instantiate(pc, name_, Location::regOf(op1));
        }
        else
        {
            stmts = instantiate(pc, name_, new Const(op1));
        }
    }
    else if (tokens.at(0) == "CLR") {
        unsigned op1 = magic_process(tokens.at(1));
        if(op1 == 8)
        {
            stmts = instantiate(pc, "CLR_A");
        }
        else
        if(op1 == 10)
        {
            stmts = instantiate(pc, "CLR_C");
        }
        else
        {
            stmts = instantiate(pc, "CLR_DIR", new Const(op1-100));
        }
    }
    else if (tokens.at(0) == "SETB" || tokens.at(0) == "SETB") {
        unsigned op1 = magic_process(tokens.at(1));
        if(op1 == 10)
        {
            stmts = instantiate(pc, "SETB_C");
        }
        else
        {
            stmts = instantiate(pc, "SETB_DIR", new Const(op1 - 100));
        }
    }
    else if (tokens.at(0) == "SWAP" || tokens.at(0) == "SWAP") {
        unsigned op1 = magic_process(tokens.at(1));
        if(op1 == 8)
        {
            stmts = instantiate(pc,"SWAP_A");
        }
    }
    else if (tokens.at(0) == "XCH" || tokens.at(0) == "XCHD") {
        unsigned op1 = magic_process(tokens.at(1));
        unsigned op2 = magic_process(tokens.at(2));
        std::stringstream sstm;
        sstm << tokens.at(0) << "_A_";
        std::string name;
        if(op1 == 8)
        {
            if(tokens.at(2) == "@R0")
            {
                sstm << "RI0";
                name = sstm.str();
                char *name_ =  new char[name.length() + 1];
                strcpy(name_, name.c_str());
                stmts = instantiate(pc, name_);
            }
            else
            if(tokens.at(2) == "@R1")
            {
                sstm << "RI1";
                name = sstm.str();
                char *name_ =  new char[name.length() + 1];
                strcpy(name_, name.c_str());
                stmts = instantiate(pc, name_);
            }
            else
            if(op2 < 8)
            {
                sstm << "R" << op2;
                name = sstm.str();
                char *name_ =  new char[name.length() + 1];
                strcpy(name_, name.c_str());
                stmts = instantiate(pc, name_);
            }
            else
            {
                sstm << "DIR";
                name = sstm.str();
                char *name_ =  new char[name.length() + 1];
                strcpy(name_, name.c_str());
                stmts = instantiate(pc, name_, new Const(op2-100));
            }
        }
    }
    else if (tokens.at(0) == "DA" || tokens.at(0) == "DA") {
        unsigned op1 = magic_process(tokens.at(1));
        if(op1 == 8)
        {
            stmts = instantiate(pc, "DA");
        }
    }
    else if (tokens.at(0) == "RL" || tokens.at(0) == "RL") {
        unsigned op1 = magic_process(tokens.at(1));
        if(op1 == 8)
        {
            stmts = instantiate(pc, "RL_A");
        }
    }