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



    #define declareRunTimeSelectionTable(autoPtr,psiReactionThermo,fvMesh,(const fvMesh& mesh, const word& phaseName),(mesh, phaseName))
        /* Construct from (const fvMesh& mesh, const word& phaseName) function pointer type */
        typedef autoPtr<psiReactionThermo> (*fvMeshConstructorPtr)(const fvMesh& mesh, const word& phaseName);

        /* Construct from (const fvMesh& mesh, const word& phaseName) function table type */
        typedef HashTable<fvMeshConstructorPtr, word, string::hash>
            fvMeshConstructorTable;

        /* Construct from (const fvMesh& mesh, const word& phaseName) function pointer table pointer */
        static fvMeshConstructorTable* fvMeshConstructorTablePtr_;

        /* Table constructor called from the table add function */
        static void constructfvMeshConstructorTables();

        /* Table destructor called from the table add function destructor */
        static void destroyfvMeshConstructorTables();

        /* Class to add constructor from (const fvMesh& mesh, const word& phaseName) to table */
        template<class psiReactionThermoType>
        class addfvMeshConstructorToTable
        {
        public:

            static autoPtr<psiReactionThermo> New (const fvMesh& mesh, const word& phaseName)
            {
                return autoPtr<psiReactionThermo>(new psiReactionThermoType (mesh, phaseName));
            }

            addfvMeshConstructorToTable
            (
                const word& lookup = psiReactionThermoType::typeName
            )
            {
                constructfvMeshConstructorTables();
                if (!fvMeshConstructorTablePtr_->insert(lookup, New))
                {
                    std::cerr<< "Duplicate entry " << lookup
                        << " in runtime selection table " << "psiReactionThermo"
                        << std::endl;
                    error::safePrintStack(std::cerr);
                }
            }

            ~addfvMeshConstructorToTable()
            {
                destroyfvMeshConstructorTables();
            }
        };

        /* Class to add constructor from (const fvMesh& mesh, const word& phaseName) to table */
        /* Remove only the entry (not the table) upon destruction */
        template<class psiReactionThermoType>
        class addRemovablefvMeshConstructorToTable
        {
            /* retain lookup name for later removal */
            const word& lookup_;

        public:

            static autoPtr<psiReactionThermo> New (const fvMesh& mesh, const word& phaseName)
            {
                return autoPtr<psiReactionThermo>(new psiReactionThermoType (mesh, phaseName));
            }

            addRemovablefvMeshConstructorToTable
            (
                const word& lookup = psiReactionThermoType::typeName
            )
            :
                lookup_(lookup)
            {
                constructfvMeshConstructorTables();
                fvMeshConstructorTablePtr_->set(lookup, New);
            }

            ~addRemovablefvMeshConstructorToTable()
            {
                if (fvMeshConstructorTablePtr_)
                {
                    fvMeshConstructorTablePtr_->erase(lookup_);
                }
            }
        };


        declareRunTimeSelectionTable
        (
            autoPtr,
            psiReactionThermo,
            fvMesh,
            (const fvMesh& mesh, const word& phaseName),
            (mesh, phaseName)
        );
