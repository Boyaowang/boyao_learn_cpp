#define defineTemplateTypeNameAndDebugWithName(Type, Name, DebugSwitch)        \
    defineTemplateTypeNameWithName(Type, Name);                                \
    defineTemplateDebugSwitchWithName(Type, Name, DebugSwitch)

    //- Define the typeName as \a Name for template classes
    #define defineTemplateTypeNameWithName(Type, Name)                             \
        template<>                                                                 \
        defineTypeNameWithName(Type, Name)

        #define defineTypeNameWithName(Type, Name)                                     \
            const ::Foam::word Type::typeName(Name)


        //- Define the debug information for templates, lookup as \a Name
    #define defineTemplateDebugSwitchWithName(Type, Name, DebugSwitch)             \
        template<>                                                                 \
        defineDebugSwitchWithName(Type, Name, DebugSwitch);                        \
        registerTemplateDebugSwitchWithName(Type, Name)

        #define defineDebugSwitchWithName(Type, Name, DebugSwitch)                     \
            int Type::debug(::Foam::debug::debugSwitch(Name, DebugSwitch))

        #define registerTemplateDebugSwitchWithName(Type,Name)                         \
            template<>                                                                 \
            const Foam::RegisterDebugSwitch<Type>                                      \
                Foam::RegisterDebugSwitch<Type>::registerDebugSwitch(Name)


    defineTemplateTypeNameAndDebugWithName
    (
        hePsiThermoreactingMixturegasHThermoPhysics,
        ("hePsiThermo""<" + reactingMixture<gasHThermoPhysics>::typeName() + ">").c_str(),0
    )



    #define declareRunTimeSelectionTable(autoPtr,baseType,argNames,argList,parList)\
                                                                                   \
        /* Construct from argList function pointer type */                         \
        typedef autoPtr<baseType> (*argNames##ConstructorPtr)argList;              \
                                                                                   \
        /* Construct from argList function table type */                           \
        typedef HashTable<argNames##ConstructorPtr, word, string::hash>            \
            argNames##ConstructorTable;                                            \
                                                                                   \
        /* Construct from argList function pointer table pointer */                \
        static argNames##ConstructorTable* argNames##ConstructorTablePtr_;         \
                                                                                   \
        /* Table constructor called from the table add function */                 \
        static void construct##argNames##ConstructorTables();                      \
                                                                                   \
        /* Table destructor called from the table add function destructor */       \
        static void destroy##argNames##ConstructorTables();                        \
                                                                                   \
        /* Class to add constructor from argList to table */                       \
        template<class baseType##Type>                                             \
        class add##argNames##ConstructorToTable                                    \
        {                                                                          \
        public:                                                                    \
                                                                                   \
            static autoPtr<baseType> New argList                                   \
            {                                                                      \
                return autoPtr<baseType>(new baseType##Type parList);              \
            }                                                                      \
                                                                                   \
            add##argNames##ConstructorToTable                                      \
            (                                                                      \
                const word& lookup = baseType##Type::typeName                      \
            )                                                                      \
            {                                                                      \
                construct##argNames##ConstructorTables();                          \
                if (!argNames##ConstructorTablePtr_->insert(lookup, New))          \
                {                                                                  \
                    std::cerr<< "Duplicate entry " << lookup                       \
                        << " in runtime selection table " << #baseType             \
                        << std::endl;                                              \
                    error::safePrintStack(std::cerr);                              \
                }                                                                  \
            }                                                                      \
                                                                                   \
            ~add##argNames##ConstructorToTable()                                   \
            {                                                                      \
                destroy##argNames##ConstructorTables();                            \
            }                                                                      \
        };                                                                         \
                                                                                   \
        /* Class to add constructor from argList to table */                       \
        /* Remove only the entry (not the table) upon destruction */               \
        template<class baseType##Type>                                             \
        class addRemovable##argNames##ConstructorToTable                           \
        {                                                                          \
            /* retain lookup name for later removal */                             \
            const word& lookup_;                                                   \
                                                                                   \
        public:                                                                    \
                                                                                   \
            static autoPtr<baseType> New argList                                   \
            {                                                                      \
                return autoPtr<baseType>(new baseType##Type parList);              \
            }                                                                      \
                                                                                   \
            addRemovable##argNames##ConstructorToTable                             \
            (                                                                      \
                const word& lookup = baseType##Type::typeName                      \
            )                                                                      \
            :                                                                      \
                lookup_(lookup)                                                    \
            {                                                                      \
                construct##argNames##ConstructorTables();                          \
                argNames##ConstructorTablePtr_->set(lookup, New);                  \
            }                                                                      \
                                                                                   \
            ~addRemovable##argNames##ConstructorToTable()                          \
            {                                                                      \
                if (argNames##ConstructorTablePtr_)                                \
                {                                                                  \
                    argNames##ConstructorTablePtr_->erase(lookup_);                \
                }                                                                  \
            }                                                                      \
        };


        declareRunTimeSelectionTable
        (
            autoPtr,
            psiReactionThermo,
            fvMesh,
            (const fvMesh& mesh, const word& phaseName),
            (mesh, phaseName)
        );
