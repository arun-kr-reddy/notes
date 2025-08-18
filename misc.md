# misc
- [personal finance](#personal-finance)
  - [ESOPs tax filing](#esops-tax-filing)
- [upskilling](#upskilling)
- [quotes](#quotes)

## todo <!-- omit from toc -->
- [google hiring assessment](https://www.reddit.com/r/csMajors/comments/1afm4ef/google_hiring_assessment/?share_id=Fk4vUGIZxi5d5klaif1bC&utm_medium=ios_app&utm_name=ioscss&utm_source=share&utm_term=1)
- **resume tips:** [1](https://www.linkedin.com/posts/you-know-who_google-resume-shortlisting-activity-7248920000315473920-mbMW/?utm_source=share&utm_medium=member_desktop), [2](https://www.linkedin.com/feed/update/urn:li:activity:7286044361849536512/), [3](https://www.reddit.com/r/developersIndia/comments/1b401so/few_tips_to_get_your_naukri_resume_shortlisted_by/)
- [resume improvement tool](https://cvcompiler.com/)
- [cold referral message](https://www.linkedin.com/feed/update/urn:li:activity:7314529008845537280/)
- [irish domiciled ETFs](https://www.reddit.com/r/IndiaInvestments/comments/jmtik0/lets_discuss_irish_domiciled_etfs_to_invest_in/)

## personal finance
- **why sell ESOPs on vest:**
  - hold only if you would buy your company stock if you had cash
  - stock falling in future and losing your job are highly correlated
  - unvested stocks & salary increments already give exposure to company's growth
- **why not track every rupee:**
  - waste of time if you've got your impulses under control and hit your savings goal
  - energy should be spent on making money and keeping yourself healthy & happy
- **why stay back in india:**
  - europe needs skilled immigrants to fund their social welfare ponzi scheme
  - wait-times for anything beyond a cold varies from several weeks to few months
  - nowadays offices in india have good salaries and big teams with decent work

### [ESOPs tax filing](https://www.youtube.com/watch?v=NO6OlUI1Hz4)
- [sample spreadsheet](https://docs.google.com/spreadsheets/d/1oIXQBw2UPs85bPaDNYrtJTxoSkKj0gQ7glok59ZK_Gs/edit?usp=sharing)
- use last monthly date's "TT BUY" [SBI rate](https://github.com/sahilgupta/sbi-fx-ratekeeper/blob/main/csv_files/SBI_REFERENCE_RATES_USD.csv) for USD to INR conversions
- form12BA has already-taxed income from combined RSU & ESPP, individual amount from tax-computation sheet
- dividends taxed by US at 25% ([etrade 1042S](https://us.etrade.com/etx/pxy/tax-center)) which can be used as tax credits by filling [itr form67](https://eportal.incometax.gov.in/iec/foservices/#/dashboard/fileIncomeTaxForm)
- **ITR2 schedules to fill:**
  - capital gains: fill combined purchase & sale price for financial year, add dividend as other sources
  - foreign source income (FSI): fill RSUs & ESPP gain
  - foreign assets (FA): fill combined purchase & sale price for calendar year
  - tax relief (TR): fill after form67

#### ESPP
- `num_shares * (purchase_date_FMV - purchase_price)` already taxed
- only need to compute profit `num_shares * (sale_price - purchase_date_FMV)` using [etrade gain & losses](https://us.etrade.com/etx/sp/stockplan#/myAccount/gainsLosses)
- ![](./media/misc/esop_taxation_espp.png)

#### RSUs
- `num_shares * vest_date_FMV` already taxed
- only need to compute profit `num_shares * (sale_price - vest_date_FMV)` using [etrade gain & losses](https://us.etrade.com/etx/sp/stockplan#/myAccount/gainsLosses)
- also figure out order pairs of auto-covered-sale (one-third shares sold on vesting) & what-you-sold
- ![](./media/misc/esop_taxation_rsu.png)

## upskilling
- **when to switch job:** can't add/update a single thing in your resume every 3 months
- **leetcode prep:**[reddit](https://www.reddit.com/r/cscareerquestions/comments/ot9ssf/comment/h6tx1vx/?utm_source=share&utm_medium=mweb3x&utm_name=mweb3xcss&utm_term=1&utm_content=share_button), [medium](https://medium.com/@rajbopche/my-preparation-for-algo-ds-193c90952d8c)
  - if can't make any progress in first 10min then mark it and look up what you need to solve it
  - short notes for each problem
    - approach & pseducode in short
    - new trick/pattern involved
    - time & space complexity
  - give yourself time to forget and retry failed problems after 2 weeks
  - goal is to understand the problem not memorize solution
  - if you can't solve new problems then you are memorizing solutions
  - getting into leetcode shape will take multiple months but getting back into it again later will just take weeks

## quotes
- *advertising has us chasing cars & clothes, working jobs we hate so we can buy shit we don't need*
- *just because you can afford it doesn't mean you should buy it*
- *AI can only replace you if your work is already done and readily accessible over the internet, AI cannot replace novelty*
- *code is read more than it is written, so code clarity trumps micro-optimization*
- *nothing more permanent than a temporary fix that works*