====================================================
Extra Clang Tools |release| |ReleaseNotesTitle|
====================================================

.. contents::
   :local:
   :depth: 3

Written by the `LLVM Team <https://llvm.org/>`_

.. only:: PreRelease

  .. warning::
     These are in-progress notes for the upcoming Extra Clang Tools |version| release.
     Release notes for previous releases can be found on
     `the Download Page <https://releases.llvm.org/download.html>`_.

Introduction
============

This document contains the release notes for the Extra Clang Tools, part of the
Clang release |release|. Here we describe the status of the Extra Clang Tools in
some detail, including major improvements from the previous release and new
feature work. All LLVM releases may be downloaded from the `LLVM releases web
site <https://llvm.org/releases/>`_.

For more information about Clang or LLVM, including information about
the latest release, please see the `Clang Web Site <https://clang.llvm.org>`_ or
the `LLVM Web Site <https://llvm.org>`_.

Note that if you are reading this file from a Git checkout or the
main Clang web page, this document applies to the *next* release, not
the current one. To see the release notes for a specific release, please
see the `releases page <https://llvm.org/releases/>`_.

What's New in Extra Clang Tools |release|?
==========================================

Some of the major new features and improvements to Extra Clang Tools are listed
here. Generic improvements to Extra Clang Tools as a whole or to its underlying
infrastructure are described first, followed by tool-specific sections.

Major New Features
------------------

...

Improvements to clangd
----------------------

Inlay hints
^^^^^^^^^^^

- This feature provides texutal hints interleaved with the code,
  like parameter names, deduced types and designated initializers.

- The `clangd/inlayHints <https://clangd.llvm.org/extensions#inlay-hints>`_
  LSP extension is now documented, and both position and range.

- Inlay hints are now on-by-default in clangd, if the client supports and
  exposes them. (`vscode-clangd
  <https://marketplace.visualstudio.com/items?itemName=llvm-vs-code-extensions.vscode-clangd>`_
  does so). The ``-inlay-hints`` flag has been removed.

- Inlay hints can be `disabled or configured
  <https://clangd.llvm.org/config#inlayhints>`_ in the config file.

Diagnostics
^^^^^^^^^^^

- `Unused #include
  <https://clangd.llvm.org/design/include-cleaner>`_ diagnostics are available.
  These are off by default, and can be turned on through the
  `Diagnostics.UnusedIncludes <https://clangd.llvm.org/config#unusedincludes>`_
  config option.

- ``Deprecated`` and ``Unnecessary`` tags from LSP 3.15 are set on
  ``-Wdeprecated`` and ``-Wunused`` diagnostics. Clients may display these
  in a specialized way.

- clangd suggests inserting includes to fix problems in more cases:

  - calling unknown functions in C, even when an implicit declaration is
    inferred.
  - incomplete types (some additional cases).
  - various diagnostics that specify "include <foo.h>" in their text.

- The "populate switch" action is more reliably offered as a fix for
  ``-Wswitch`` warnings, and works with C enums.

- Warnings specified by ``ExtraArgs: -W...`` flags in ``.clang-tidy`` config
  files are now produced.

Semantic Highlighting
^^^^^^^^^^^^^^^^^^^^^

- ``virtual`` modifier for method names
- ``usedAsMutableReference`` modifier for function parameters
- Lambda captures now marked as local variables.

Compile flags
^^^^^^^^^^^^^

- Compile flags like ``-xc++-header`` that must precede input file names are now
  added correctly by the
  `CompileFlags.Add <https://clangd.llvm.org/config#add>`_ config option.

- If multiple architectures are specified (e.g. when targeting Apple M1+Intel),
  clangd will now use the host architecture instead of failing to parse.

- Added `CompileFlags.Compiler <https://clangd.llvm.org/config#compiler>`_
  option to override executable name in compile flags.

- Copying ``compile_commands.json`` entries from one file to another (and simply
  adjusting ``file``) should now work correctly.

Hover
^^^^^

- Hovering on many attributes (e.g. ``[[nodiscard]]``) will show documentation.
- Hovering on include directives shows the resolved header path.
- Hovering on character literals shows their numeric value.
- Code snippets are marked with the appropriate language instead of always C++.
  This may improve clients' syntax highlighting.
- Include desugared types in hover, like in diagnostics.
  Off by default, controlled with `Hover.ShowAKA
  <https://clangd.llvm.org/config#showaka>`_ config option.

Code completion
^^^^^^^^^^^^^^^

- Completion of attributes (e.g. ``[[gsl::Owner(Foo)]]``)
- Completion of ``/*ParameterName=*/`` comments.
- Documentation of items with ``annotate`` attributes now includes the
  annotation.
- Improved handling of results with 1-3 character names.
- Completion of members in constructor init lists (``Foo() : member_() {}``) is
  much more reliable.
- C++ Standard library completions should be less noisy: parameter names are
  deuglified (``vector<_Tp>`` is now ``vector<Tp>``) and many
  ``__implementation_details`` are hidden altogether.

Signature help
^^^^^^^^^^^^^^

- Signatures for template argument lists
- Signatures for braced constructor calls
- Signatures for aggregate initializers
- Signatures for members in constructor init lists are much more reliable.
- Variadic functions correctly show signature help when typing the variadic
  arguments.
- Signature help is retriggered on closing brackets ``)``, ``}``, ``>``.
  This means signature help should be correct after nested function calls.

Cross-references
^^^^^^^^^^^^^^^^

- Support for ``textDocument/typeDefinition`` LSP request.
- Improved handling of symbols introduced via using declarations.
- Searching for references to an overriding method also returns references to
  the base class method. (Typically calls that may invoke the override).
- All references from the current file are always returned, even if there are
  enough to exceed our usual limit.

Objective-C
^^^^^^^^^^^

- ``#pragma mark`` directives now form groups in the document outline.
- ``id`` and ``instancetype`` are treated as keywords rather than typedefs

Miscellaneous
^^^^^^^^^^^^^

- Include request context on crashes when possible.
- Many stability, performance and correctness improvements.
- ``-use-dirty-headers`` command line flag to use dirty buffer contents when
  parsing headers, rather than the saved on-disk contents.
- ``clangd --check=/path/to/file.cpp`` now reads config files in ancestor
  directories, in addition to user config file.
- Improved compile flags handling in ``clangd-indexer``.
- The index file format changed in this release, indexes need to be rebuilt.
  This should happen transparently in standard cases (the background index).

Improvements to clang-doc
-------------------------

The improvements are...

Improvements to clang-query
---------------------------

The improvements are...

Improvements to clang-rename
----------------------------

The improvements are...

Improvements to clang-tidy
--------------------------

- Ignore warnings from macros defined in system headers, if not using the
  `-system-headers` flag.

- Added support for globbing in `NOLINT*` expressions, to simplify suppressing
  multiple warnings in the same line.

- Added support for `NOLINTBEGIN` ... `NOLINTEND` comments to suppress
  Clang-Tidy warnings over multiple lines.

- Added support for external plugin checks with `-load`.

New checks
^^^^^^^^^^

- New :doc:`abseil-cleanup-ctad
  <clang-tidy/checks/abseil-cleanup-ctad>` check.

  Suggests switching the initialization pattern of ``absl::Cleanup``
  instances from the factory function to class template argument
  deduction (CTAD), in C++17 and higher.

- New :doc:`bugprone-stringview-nullptr
  <clang-tidy/checks/bugprone-stringview-nullptr>` check.

  Checks for various ways that the ``const CharT*`` constructor of
  ``std::basic_string_view`` can be passed a null argument.

- New :doc:`bugprone-suspicious-memory-comparison
  <clang-tidy/checks/bugprone-suspicious-memory-comparison>` check.

  Finds potentially incorrect calls to ``memcmp()`` based on properties of the
  arguments.

- New :doc:`cppcoreguidelines-virtual-class-destructor
  <clang-tidy/checks/cppcoreguidelines-virtual-class-destructor>` check.

  Finds virtual classes whose destructor is neither public and virtual nor
  protected and non-virtual.

- New :doc:`gjb-a1-b1-c1-forbidden-duplicate-procedure-name
  <clang-tidy/checks/gjb-a1-b1-c1-forbidden-duplicate-procedure-name>` check.

  FIXME: add release notes.

- New :doc:`gjb-a1-b1-c10-forbidden-empty-param-table
  <clang-tidy/checks/gjb-a1-b1-c10-forbidden-empty-param-table>` check.

  FIXME: add release notes.

- New :doc:`gjb-a1-b1-c11-forbidden-multiple-pounds-in-macro
  <clang-tidy/checks/gjb-a1-b1-c11-forbidden-multiple-pounds-in-macro>` check.

  FIXME: add release notes.

- New :doc:`gjb-a1-b1-c15-the-sign-of-char
  <clang-tidy/checks/gjb-a1-b1-c15-the-sign-of-char>` check.

  FIXME: add release notes.

- New :doc:`gjb-a1-b1-c16-forbidden-redefine-name
  <clang-tidy/checks/gjb-a1-b1-c16-forbidden-redefine-name>` check.

  FIXME: add release notes.

- New :doc:`gjb-a1-b1-c17-forbidden-redefine-typedef
  <clang-tidy/checks/gjb-a1-b1-c17-forbidden-redefine-typedef>` check.

  FIXME: add release notes.

- New :doc:`gjb-a1-b1-c19-forbidden-array-without-boundary
  <clang-tidy/checks/gjb-a1-b1-c19-forbidden-array-without-boundary>` check.

  FIXME: add release notes.

- New :doc:`gjb-a1-b1-c2-forbidden-duplicate-label-name
  <clang-tidy/checks/gjb-a1-b1-c2-forbidden-duplicate-label-name>` check.

  FIXME: add release notes.

- New :doc:`gjb-a1-b1-c21-forbidden-incomplete-struct-decl
  <clang-tidy/checks/gjb-a1-b1-c21-forbidden-incomplete-struct-decl>` check.

  FIXME: add release notes.

- New :doc:`gjb-a1-b1-c22-forbidden-inconsistent-param-decl
  <clang-tidy/checks/gjb-a1-b1-c22-forbidden-inconsistent-param-decl>` check.

  FIXME: add release notes.

- New :doc:`gjb-a1-b1-c4-forbidden-multiple-labels-declaration
  <clang-tidy/checks/gjb-a1-b1-c4-forbidden-multiple-labels-declaration>` check.

  FIXME: add release notes.

- New :doc:`gjb-a1-b1-c5-parameter-use-type-description
  <clang-tidy/checks/gjb-a1-b1-c5-parameter-use-type-description>` check.

  FIXME: add release notes.

- New :doc:`gjb-a1-b1-c6-parameter-be-specified-in-procedure-declaration
  <clang-tidy/checks/gjb-a1-b1-c6-parameter-be-specified-in-procedure-declaration>` check.

  FIXME: add release notes.

- New :doc:`gjb-a1-b1-c7-forbidden-no-identifier-parameter
  <clang-tidy/checks/gjb-a1-b1-c7-forbidden-no-identifier-parameter>` check.

  FIXME: add release notes.

- New :doc:`gjb-a1-b1-c8-forbidden-ellipsis-in-parameter
  <clang-tidy/checks/gjb-a1-b1-c8-forbidden-ellipsis-in-parameter>` check.

  FIXME: add release notes.

- New :doc:`gjb-a1-b1-c9-forbidden-redefine-keyword
  <clang-tidy/checks/gjb-a1-b1-c9-forbidden-redefine-keyword>` check.

  FIXME: add release notes.

- New :doc:`gjb-a1-b2-c2-forbidden-define-func-as-parms
  <clang-tidy/checks/gjb-a1-b2-c2-forbidden-define-func-as-parms>` check.

  FIXME: add release notes.

- New :doc:`gjb-a1-b2-c3-forbidden-many-parms
  <clang-tidy/checks/gjb-a1-b2-c3-forbidden-many-parms>` check.

  FIXME: add release notes.

- New :doc:`gjb-a1-b2-c4-bit-field-cautiously
  <clang-tidy/checks/gjb-a1-b2-c4-bit-field-cautiously>` check.

  FIXME: add release notes.

- New :doc:`gjb-a1-b2-c8-use-union-cautiously
  <clang-tidy/checks/gjb-a1-b2-c8-use-union-cautiously>` check.

  FIXME: add release notes.

- New :doc:`gjb-a1-b2-c9-nameless-bit-field-cautiously
  <clang-tidy/checks/gjb-a1-b2-c9-nameless-bit-field-cautiously>` check.

  FIXME: add release notes.

- New :doc:`gjb-a10-b1-c1-forbid--nested-comment
  <clang-tidy/checks/gjb-a10-b1-c1-forbid--nested-comment>` check.

  FIXME: add release notes.

- New :doc:`gjb-a10-b2-c2-avoid-single-line-comment
  <clang-tidy/checks/gjb-a10-b2-c2-avoid-single-line-comment>` check.

  FIXME: add release notes.

- New :doc:`gjb-a2-b1-c10-form-of-main
  <clang-tidy/checks/gjb-a2-b1-c10-form-of-main>` check.

  FIXME: add release notes.

- New :doc:`gjb-a2-b1-c2-braces-around-loop
  <clang-tidy/checks/gjb-a2-b1-c2-braces-around-loop>` check.

  FIXME: add release notes.

- New :doc:`gjb-a2-b1-c3-braces-around-if
  <clang-tidy/checks/gjb-a2-b1-c3-braces-around-if>` check.

  FIXME: add release notes.

- New :doc:`gjb-a2-b1-c4-paren-around-logical-expr
  <clang-tidy/checks/gjb-a2-b1-c4-paren-around-logical-expr>` check.

  FIXME: add release notes.

- New :doc:`gjb-a2-b1-c9-backslash-of-str
  <clang-tidy/checks/gjb-a2-b1-c9-backslash-of-str>` check.

  FIXME: add release notes.

- New :doc:`gjb-a2-b2-c1-total-lines-of-file
  <clang-tidy/checks/gjb-a2-b2-c1-total-lines-of-file>` check.

  FIXME: add release notes.

- New :doc:`gjb-a2-b2-c2-total-lines-of-function
  <clang-tidy/checks/gjb-a2-b2-c2-total-lines-of-function>` check.

  FIXME: add release notes.

- New :doc:`gjb-a3-b1-c1-forbidden-cond-no-stmt
  <clang-tidy/checks/gjb-a3-b1-c1-forbidden-cond-no-stmt>` check.

  FIXME: add release notes.

- New :doc:`gjb-a3-b1-c2-must-use-else
  <clang-tidy/checks/gjb-a3-b1-c2-must-use-else>` check.

  FIXME: add release notes.

- New :doc:`gjb-a3-b1-c3-forbidden-else-no-stmt
  <clang-tidy/checks/gjb-a3-b1-c3-forbidden-else-no-stmt>` check.

  FIXME: add release notes.

- New :doc:`gjb-a3-b1-c4-switch-must-have-default
  <clang-tidy/checks/gjb-a3-b1-c4-switch-must-have-default>` check.

  FIXME: add release notes.

- New :doc:`gjb-a3-b1-c5-forbidden-empty-switch
  <clang-tidy/checks/gjb-a3-b1-c5-forbidden-empty-switch>` check.

  FIXME: add release notes.

- New :doc:`gjb-a3-b1-c6-forbidden-switch-only-default
  <clang-tidy/checks/gjb-a3-b1-c6-forbidden-switch-only-default>` check.

  FIXME: add release notes.

- New :doc:`gjb-a3-b1-c7-forbidden-case-no-break
  <clang-tidy/checks/gjb-a3-b1-c7-forbidden-case-no-break>` check.

  FIXME: add release notes.

- New :doc:`gjb-a3-b1-c8-forbidden-empty-case
  <clang-tidy/checks/gjb-a3-b1-c8-forbidden-empty-case>` check.

  FIXME: add release notes.

- New :doc:`gjb-a4-b1-c2-forbidden-pointer-level-triple
  <clang-tidy/checks/gjb-a4-b1-c2-forbidden-pointer-level-triple>` check.

  FIXME: add release notes.

- New :doc:`gjb-a4-b1-c3-forbidden-proc-pointer
  <clang-tidy/checks/gjb-a4-b1-c3-forbidden-proc-pointer>` check.

  FIXME: add release notes.

- New :doc:`gjb-a4-b2-c1-compare-pointer
  <clang-tidy/checks/gjb-a4-b2-c1-compare-pointer>` check.

  FIXME: add release notes.

- New :doc:`gjb-a4-b2-c2-operation-on-pointer
  <clang-tidy/checks/gjb-a4-b2-c2-operation-on-pointer>` check.

  FIXME: add release notes.

- New :doc:`gjb-a5-b1-c1-forbidden-jump-func-directly
  <clang-tidy/checks/gjb-a5-b1-c1-forbidden-jump-func-directly>` check.

  FIXME: add release notes.

- New :doc:`gjb-a5-b1-c2-forbidden-goto
  <clang-tidy/checks/gjb-a5-b1-c2-forbidden-goto>` check.

  FIXME: add release notes.

- New :doc:`gjb-a5-b2-c1-avoid-setjmp-longjmp
  <clang-tidy/checks/gjb-a5-b2-c1-avoid-setjmp-longjmp>` check.

  FIXME: add release notes.

- New :doc:`gjb-a6-b1-c1-assign-op-with-assign-expr
  <clang-tidy/checks/gjb-a6-b1-c1-assign-op-with-assign-expr>` check.

  FIXME: add release notes.

- New :doc:`gjb-a6-b1-c11-negation-to-constant
  <clang-tidy/checks/gjb-a6-b1-c11-negation-to-constant>` check.

  FIXME: add release notes.

- New :doc:`gjb-a6-b1-c12-bitwise-on-signed-type
  <clang-tidy/checks/gjb-a6-b1-c12-bitwise-on-signed-type>` check.

  FIXME: add release notes.

- New :doc:`gjb-a6-b1-c15-forbid-assignment-in-logical-expr
  <clang-tidy/checks/gjb-a6-b1-c15-forbid-assignment-in-logical-expr>` check.

  FIXME: add release notes.

- New :doc:`gjb-a6-b1-c16-use-assignment-operator-with
  <clang-tidy/checks/gjb-a6-b1-c16-use-assignment-operator-with>` check.

  FIXME: add release notes.

- New :doc:`gjb-a6-b1-c17-bitwise-operator-with-bool
  <clang-tidy/checks/gjb-a6-b1-c17-bitwise-operator-with-bool>` check.

  FIXME: add release notes.

- New :doc:`gjb-a6-b1-c18-bitwise-operator-act-on-bool
  <clang-tidy/checks/gjb-a6-b1-c18-bitwise-operator-act-on-bool>` check.

  FIXME: add release notes.

- New :doc:`gjb-a6-b1-c2-array-out-of-bound
  <clang-tidy/checks/gjb-a6-b1-c2-array-out-of-bound>` check.

  FIXME: add release notes.

- New :doc:`gjb-a6-b1-c3-shift-signed-type
  <clang-tidy/checks/gjb-a6-b1-c3-shift-signed-type>` check.

  FIXME: add release notes.

- New :doc:`gjb-a6-b1-c4-overflow-of-shift
  <clang-tidy/checks/gjb-a6-b1-c4-overflow-of-shift>` check.

  FIXME: add release notes.

- New :doc:`gjb-a6-b1-c5-negative-to-unsigned
  <clang-tidy/checks/gjb-a6-b1-c5-negative-to-unsigned>` check.

  FIXME: add release notes.

- New :doc:`gjb-a6-b1-c6-Bit-length-of-signed-type
  <clang-tidy/checks/gjb-a6-b1-c6-Bit-length-of-signed-type>` check.

  FIXME: add release notes.

- New :doc:`gjb-a6-b1-c7-Bit-field-type-is-int
  <clang-tidy/checks/gjb-a6-b1-c7-Bit-field-type-is-int>` check.

  FIXME: add release notes.

- New :doc:`gjb-a6-b1-c8-forbid-inconsistent-type
  <clang-tidy/checks/gjb-a6-b1-c8-forbid-inconsistent-type>` check.

  FIXME: add release notes.

- New :doc:`gjb-a6-b1-c9-Assign-type-match
  <clang-tidy/checks/gjb-a6-b1-c9-Assign-type-match>` check.

  FIXME: add release notes.

- New :doc:`gjb-a6-b2-c1-avoid-comma-operator
  <clang-tidy/checks/gjb-a6-b2-c1-avoid-comma-operator>` check.

  FIXME: add release notes.

- New :doc:`gjb-a6-b2-c2-side-effects-of-sizeof
  <clang-tidy/checks/gjb-a6-b2-c2-side-effects-of-sizeof>` check.

  FIXME: add release notes.

- New :doc:`gjb-a6-b2-c3-mixe-diff-type
  <clang-tidy/checks/gjb-a6-b2-c3-mixe-diff-type>` check.

  FIXME: add release notes.

- New :doc:`gjb-a6-b2-c4-code-cannot-be-executed
  <clang-tidy/checks/gjb-a6-b2-c4-code-cannot-be-executed>` check.

  FIXME: add release notes.

- New :doc:`gjb-a7-b1-c1-number-of-params
  <clang-tidy/checks/gjb-a7-b1-c1-number-of-params>` check.

  FIXME: add release notes.

- New :doc:`gjb-a7-b1-c10-func-type-consistent
  <clang-tidy/checks/gjb-a7-b1-c10-func-type-consistent>` check.

  FIXME: add release notes.

- New :doc:`gjb-a7-b1-c2-forbid-no-call-procedure
  <clang-tidy/checks/gjb-a7-b1-c2-forbid-no-call-procedure>` check.

  FIXME: add release notes.

- New :doc:`gjb-a7-b1-c3-must-call-static
  <clang-tidy/checks/gjb-a7-b1-c3-must-call-static>` check.

  FIXME: add release notes.

- New :doc:`gjb-a7-b1-c5-no-extern
  <clang-tidy/checks/gjb-a7-b1-c5-no-extern>` check.

  FIXME: add release notes.

- New :doc:`gjb-a7-b1-c6-forbid-call-multiple-func
  <clang-tidy/checks/gjb-a7-b1-c6-forbid-call-multiple-func>` check.

  FIXME: add release notes.

- New :doc:`gjb-a7-b1-c8-forbid-void-as-para
  <clang-tidy/checks/gjb-a7-b1-c8-forbid-void-as-para>` check.

  FIXME: add release notes.

- New :doc:`gjb-a7-b1-c9-forbid-diff-para-type
  <clang-tidy/checks/gjb-a7-b1-c9-forbid-diff-para-type>` check.

  FIXME: add release notes.

- New :doc:`gjb-a7-b2-c1-avoid-unused-para
  <clang-tidy/checks/gjb-a7-b2-c1-avoid-unused-para>` check.

  FIXME: add release notes.

- New :doc:`gjb-a7-b2-c2-avoid-using-non-call-func
  <clang-tidy/checks/gjb-a7-b2-c2-avoid-using-non-call-func>` check.

  FIXME: add release notes.

- New :doc:`gjb-a7-b2-c3-avoid-abort-or-exit
  <clang-tidy/checks/gjb-a7-b2-c3-avoid-abort-or-exit>` check.

  FIXME: add release notes.

- New :doc:`gjb-a8-b1-c1-forbid-l-or-O-as-var
  <clang-tidy/checks/gjb-a8-b1-c1-forbid-l-or-O-as-var>` check.

  FIXME: add release notes.

- New :doc:`gjb-a8-b1-c3-annotate-octal
  <clang-tidy/checks/gjb-a8-b1-c3-annotate-octal>` check.

  FIXME: add release notes.

- New :doc:`gjb-a8-b2-c1-avoid-compound-operator
  <clang-tidy/checks/gjb-a8-b2-c1-avoid-compound-operator>` check.

  FIXME: add release notes.

- New :doc:`gjb-a8-b2-c2-avoid-Increment-operator
  <clang-tidy/checks/gjb-a8-b2-c2-avoid-Increment-operator>` check.

  FIXME: add release notes.

- New :doc:`gjb-a8-b2-c3-avoid-continue
  <clang-tidy/checks/gjb-a8-b2-c3-avoid-continue>` check.

  FIXME: add release notes.

- New :doc:`gjb-a8-b2-c4-avoid-triple-expr
  <clang-tidy/checks/gjb-a8-b2-c4-avoid-triple-expr>` check.

  FIXME: add release notes.

- New :doc:`gjb-a8-b2-c5-avoid-unused-stmt
  <clang-tidy/checks/gjb-a8-b2-c5-avoid-unused-stmt>` check.

  FIXME: add release notes.

- New :doc:`gjb-a8-b2-c6-avoid-empty-stmt
  <clang-tidy/checks/gjb-a8-b2-c6-avoid-empty-stmt>` check.

  FIXME: add release notes.

- New :doc:`gjb-a8-b2-c7-register-var
  <clang-tidy/checks/gjb-a8-b2-c7-register-var>` check.

  FIXME: add release notes.

- New :doc:`gjb-a9-b1-c1-func-has-return
  <clang-tidy/checks/gjb-a9-b1-c1-func-has-return>` check.

  FIXME: add release notes.

- New :doc:`gjb-a9-b1-c2-forbid-void-returning-value
  <clang-tidy/checks/gjb-a9-b1-c2-forbid-void-returning-value>` check.

  FIXME: add release notes.

- New :doc:`gjb-a9-b1-c3-non-void-return-value
  <clang-tidy/checks/gjb-a9-b1-c3-non-void-return-value>` check.

  FIXME: add release notes.

- New :doc:`gjb-a9-b1-c4-func-return-type
  <clang-tidy/checks/gjb-a9-b1-c4-func-return-type>` check.

  FIXME: add release notes.

- New :doc:`gjb-a9-b1-c5-Func-proto-return-type
  <clang-tidy/checks/gjb-a9-b1-c5-Func-proto-return-type>` check.

  FIXME: add release notes.

- New :doc:`gjb-forbidden-empty-fields-struct
  <clang-tidy/checks/gjb-forbidden-empty-fields-struct>` check.

  FIXME: add release notes.

- New :doc:`gjb-if-has-brace
  <clang-tidy/checks/gjb-if-has-brace>` check.

  FIXME: add release notes.

- New :doc:`gjb-if_has_brace
  <clang-tidy/checks/gjb-if_has_brace>` check.

  FIXME: add release notes.

- New :doc:`gjb-my-first-check
  <clang-tidy/checks/gjb-my-first-check>` check.

  FIXME: add release notes.

- New :doc:`misc-misleading-bidirectional <clang-tidy/checks/misc-misleading-bidirectional>` check.

  Inspects string literal and comments for unterminated bidirectional Unicode
  characters.

- New :doc:`misc-misleading-identifier <clang-tidy/checks/misc-misleading-identifier>` check.

  Reports identifier with unicode right-to-left characters.

- New :doc:`readability-container-contains
  <clang-tidy/checks/readability-container-contains>` check.

  Finds usages of ``container.count()`` and ``container.find() == container.end()`` which should
  be replaced by a call to the ``container.contains()`` method introduced in C++20.

- New :doc:`readability-container-data-pointer
  <clang-tidy/checks/readability-container-data-pointer>` check.

  Finds cases where code could use ``data()`` rather than the address of the
  element at index 0 in a container.

- New :doc:`readability-duplicate-include
  <clang-tidy/checks/readability-duplicate-include>` check.

  Looks for duplicate includes and removes them.

- New :doc:`readability-identifier-length
  <clang-tidy/checks/readability-identifier-length>` check.

  Reports identifiers whose names are too short. Currently checks local
  variables and function parameters only.

New check aliases
^^^^^^^^^^^^^^^^^

- New alias :doc:`cert-err33-c
  <clang-tidy/checks/cert-err33-c>` to
  :doc:`bugprone-unused-return-value
  <clang-tidy/checks/bugprone-unused-return-value>` was added.

- New alias :doc:`cert-exp42-c
  <clang-tidy/checks/cert-exp42-c>` to
  :doc:`bugprone-suspicious-memory-comparison
  <clang-tidy/checks/bugprone-suspicious-memory-comparison>` was added.

- New alias :doc:`cert-flp37-c
  <clang-tidy/checks/cert-flp37-c>` to
  :doc:`bugprone-suspicious-memory-comparison
  <clang-tidy/checks/bugprone-suspicious-memory-comparison>` was added.

Changes in existing checks
^^^^^^^^^^^^^^^^^^^^^^^^^^

- :doc:`bugprone-assert-side-effect
  <clang-tidy/checks/bugprone-assert-side-effect>` check now supports an
  ``IgnoredFunctions`` option to explicitly consider the specified
  semicolon-separated functions list as not having any side-effects.
  Regular expressions for the list items are also accepted.

- Fixed a false positive in :doc:`bugprone-throw-keyword-missing
  <clang-tidy/checks/bugprone-throw-keyword-missing>` when creating an
  exception object using placement new.

- Removed default setting ``cppcoreguidelines-explicit-virtual-functions.IgnoreDestructors = "true"``,
  from :doc:`cppcoreguidelines-explicit-virtual-functions
  <clang-tidy/checks/cppcoreguidelines-explicit-virtual-functions>`
  to match the current state of the C++ Core Guidelines.

- Eliminated false positives for :doc:`cppcoreguidelines-macro-usage
  <clang-tidy/checks/cppcoreguidelines-macro-usage>` by restricting
  the warning about using constants to only macros that expand to literals.

- :doc:`cppcoreguidelines-narrowing-conversions
  <clang-tidy/checks/cppcoreguidelines-narrowing-conversions>`
  check now supports a ``WarnOnIntegerToFloatingPointNarrowingConversion``
  option to control whether to warn on narrowing integer to floating-point
  conversions.

- Make the :doc:`cppcoreguidelines-pro-bounds-array-to-pointer-decay
  <clang-tidy/checks/cppcoreguidelines-pro-bounds-array-to-pointer-decay>`
  check accept string literal to pointer decay in conditional operator even
  if operands are of the same length.

- Removed suggestion ``use gsl::at`` from warning message in the
  :doc:`cppcoreguidelines-pro-bounds-constant-array-index
  <clang-tidy/checks/cppcoreguidelines-pro-bounds-constant-array-index>`
  check, since that is not a requirement from the C++ Core Guidelines.
  This allows people to choose their own safe indexing strategy. The
  fix-it is kept for those who want to use the GSL library.

- Fixed a false positive in :doc:`fuchsia-trailing-return
  <clang-tidy/checks/fuchsia-trailing-return>` for C++17 deduction guides.

- Updated :doc:`google-readability-casting
  <clang-tidy/checks/google-readability-casting>` to diagnose and fix
  functional casts, to achieve feature parity with the corresponding
  ``cpplint.py`` check.

- Generalized the :doc:`modernize-use-default-member-init
  <clang-tidy/checks/modernize-use-default-member-init>` check to handle
  non-default constructors.

- Improved :doc:`performance-move-const-arg
  <clang-tidy/checks/performance-move-const-arg>` check.

  Removed a wrong FixIt for trivially copyable objects wrapped by
  ``std::move()`` and passed to an rvalue reference parameter. Removal of
  ``std::move()`` would break the code.

- :doc:`readability-simplify-boolean-expr
  <clang-tidy/checks/readability-simplify-boolean-expr>` now simplifies
  return statements associated with ``case``, ``default`` and labeled
  statements.

- Fixed a crash in :doc:`readability-suspicious-call-argument
  <clang-tidy/checks/readability-suspicious-call-argument>` related to passing
  arguments that refer to program elements without a trivial identifier.

Removed checks
^^^^^^^^^^^^^^

Improvements to include-fixer
-----------------------------

The improvements are...

Improvements to clang-include-fixer
-----------------------------------

The improvements are...

Improvements to modularize
--------------------------

The improvements are...

Improvements to pp-trace
------------------------

The improvements are...

Clang-tidy Visual Studio plugin
-------------------------------
